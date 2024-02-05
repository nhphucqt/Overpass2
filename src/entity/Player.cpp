#include <Player.hpp>
#include <CommandQueue.hpp>

#include <map>
#include <string>
#include <algorithm>

PlayerMover::PlayerMover(int x, int y): direction(x, y) {}

void PlayerMover::operator() (PlayerNode& player, sf::Time) const {
	player.pushAction(direction);
}

Player::Player(ViewCategory::Type category): mTargetCategory(category) {
	// Set initial key bindings
	mKeyBinding[sf::Keyboard::Left] = Action::MoveLeft;
	mKeyBinding[sf::Keyboard::Right] = Action::MoveRight;
	mKeyBinding[sf::Keyboard::Up] = Action::MoveUp;
	mKeyBinding[sf::Keyboard::Down] = Action::MoveDown;

	// Set initial action bindings
	initializeActions();	

	// Assign all categories to player's aircraft
	for(auto& pair : mActionBinding)
		pair.second.category = getTargetCategory();
}

void Player::setActionKeys(sf::Keyboard::Key left, 
							sf::Keyboard::Key right, 
							sf::Keyboard::Key up, 
							sf::Keyboard::Key down) {
	assignKey(Action::MoveLeft, left);
	assignKey(Action::MoveRight, right);
	assignKey(Action::MoveUp, up);
	assignKey(Action::MoveDown, down);
}

void Player::setTargetCategory(ViewCategory::Type category) {
	mTargetCategory = category;
}

ViewCategory::Type Player::getTargetCategory() const {
	return mTargetCategory;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands) {
	if (event.type == sf::Event::KeyPressed)
	{
		// Check if pressed key appears in key binding, trigger command if so
		auto found = mKeyBinding.find(event.key.code);
		if (found != mKeyBinding.end() && isRealtimeAction(found->second)) {
			commands.push(mActionBinding[found->second]);
		}
	}
}

void Player::handleRealtimeInput(CommandQueue& commands) {
	// Traverse all assigned keys and check if they are pressed
	for(auto& pair : mKeyBinding)
	{
		// If key is pressed, lookup action and trigger corresponding command
		if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
			commands.push(mActionBinding[pair.second]);
	}
}

void Player::assignKey(Action action, sf::Keyboard::Key key) {
	// Remove all keys that already map to action
	for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end(); )
	{
		if (itr->second == action)
			mKeyBinding.erase(itr++);
		else
			++itr;
	}

	// Insert new binding
	mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const {
	for(auto& pair : mKeyBinding)
	{
		if (pair.second == action)
			return pair.first;
	}

	return sf::Keyboard::Unknown;
}

void Player::initializeActions() {
	const float playerSpeed = 400.f;

	mActionBinding[Action::MoveLeft].action	 = derivedAction<PlayerNode>(PlayerMover(-1, 0));
	mActionBinding[Action::MoveRight].action = derivedAction<PlayerNode>(PlayerMover(1, 0));
	mActionBinding[Action::MoveUp].action    = derivedAction<PlayerNode>(PlayerMover(0, -1));
	mActionBinding[Action::MoveDown].action  = derivedAction<PlayerNode>(PlayerMover(0, 1));
}

bool Player::isRealtimeAction(Action action) {
	switch (action)
	{
		case Action::MoveLeft:
		case Action::MoveRight:
		case Action::MoveDown:
		case Action::MoveUp:
			return true;
		default:
			return false;
	}
}