#include "GamePlay.h"
#include "ControlMusic.h"

void GamePlay::checkGround_2()
{
	Vec2 _mapPos = _tileMap->getPosition();

	// down
	for (int i = 0; i < _Line_Down_Pos.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Down_Pos.at(i).y == _Line_Down_Pos.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos.at(i).x == _Line_Down_Pos.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos.at(i + 1).y - (0 - _mapPos.y) - 50)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.y <= _Line_Down_Pos.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}

		// rock
		for (int j = 0; j < rocks.size(); j++) {
			float x = rocks.at(j)->GetSprite()->getPosition().x;
			float y = rocks.at(j)->GetSprite()->getPosition().y;
			if (y <= _Line_Down_Pos.at(i).y - (0 - _mapPos.y) &&
				(y >= _Line_Down_Pos.at(i).y - (0 - _mapPos.y) - 20) &&
				(x >= _Line_Down_Pos.at(i).x - (0 - _mapPos.x)) &&
				(x <= _Line_Down_Pos.at(i + 1).x - (0 - _mapPos.x))) {
				rocks.at(j)->GetSprite()->setPosition(x, _Line_Down_Pos.at(i).y - (0 - _mapPos.y));
				rocks.at(j)->GetSprite()->getPhysicsBody()->setGravityEnable(false);
			}
		}
	}

	for (int i = 0; i < _Line_Down_Pos_2.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Down_Pos_2.at(i).y == _Line_Down_Pos_2.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_2.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_2.at(i).x == _Line_Down_Pos_2.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_2.at(i + 1).y - (0 - _mapPos.y) - 50)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_2.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_2.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.y <= _Line_Down_Pos_2.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_2.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Down_Pos_3.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();

		// ngang
		if (_Line_Down_Pos_3.at(i).y == _Line_Down_Pos_3.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y) - 10) &&
				(_main_pos.x >= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_3.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_3.at(i).x == _Line_Down_Pos_3.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_3.at(i + 1).y - (0 - _mapPos.y) - 50)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_3.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y > _Line_Down_Pos_3.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.y < _Line_Down_Pos_3.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_3.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Down_Pos_4.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();

		// ngang
		if (_Line_Down_Pos_4.at(i).y == _Line_Down_Pos_4.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y) - 10) &&
				(_main_pos.x >= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_4.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_4.at(i).x == _Line_Down_Pos_4.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y <= _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_4.at(i + 1).y - (0 - _mapPos.y) - 50)) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_4.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_4.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.y <= _Line_Down_Pos_4.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_4.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Down_Pos_5.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();

		// ngang
		if (_Line_Down_Pos_5.at(i).y == _Line_Down_Pos_5.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x >= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Down_Pos_5.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_5.at(i).x == _Line_Down_Pos_5.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.y <= _Line_Down_Pos_5.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_5.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			/*else if ((_main_pos.x <= _Line_Down_Pos.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_5.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.y <= _Line_Down_Pos_5.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_5.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}*/
		}


	}

	for (int i = 0; i < _Line_Down_Pos_6.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();

		// ngang
		if (_Line_Down_Pos_6.at(i).y == _Line_Down_Pos_6.at(i + 1).y) {
			if ((_main_pos.y <= _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y >= _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.x <= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_6.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Down_Pos_6.at(i).x == _Line_Down_Pos_6.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.y <= _Line_Down_Pos_6.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_6.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			/*else if ((_main_pos.x <= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Down_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y >= _Line_Down_Pos_6.at(i).y - (0 - _mapPos.y) - 50) &&
				(_main_pos.y <= _Line_Down_Pos_6.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->getPhysicsBody()->setGravityEnable(false);
				main_charactor->GetSprite()->setPosition(_Line_Down_Pos_6.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}*/
		}
	}

	// up
	for (int i = 0; i < _Line_Up_Pos_1.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		//ngang
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_1.at(i).y == _Line_Up_Pos_1.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_1.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_1.at(i).x == _Line_Up_Pos_1.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_1.at(i + 1).y - (0 - _mapPos.y) + 10)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_1.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_1.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_1.at(i).y - (0 - _mapPos.y) + 50) &&
				(_main_pos.y >= _Line_Up_Pos_1.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_1.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_2.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		// ngang
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_2.at(i).y == _Line_Up_Pos_2.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_2.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_2.at(i).x == _Line_Up_Pos_2.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_2.at(i + 1).y - (0 - _mapPos.y) + 50)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_2.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_2.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_2.at(i).y - (0 - _mapPos.y) + 50) &&
				(_main_pos.y >= _Line_Up_Pos_2.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_2.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_3.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		// ngang
		if (_Line_Up_Pos_3.at(i).y == _Line_Up_Pos_3.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_3.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_3.at(i).x == _Line_Up_Pos_3.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_3.at(i + 1).y - (0 - _mapPos.y) + 50)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_3.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_3.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_3.at(i).y - (0 - _mapPos.y) + 50) &&
				(_main_pos.y >= _Line_Up_Pos_3.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_3.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_4.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_4.at(i).y == _Line_Up_Pos_4.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_4.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_4.at(i).x == _Line_Up_Pos_4.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_4.at(i + 1).y - (0 - _mapPos.y) + 50)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_4.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_4.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_4.at(i).y - (0 - _mapPos.y) + 50) &&
				(_main_pos.y >= _Line_Up_Pos_4.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_4.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_5.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_5.at(i).y == _Line_Up_Pos_5.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_5.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_5.at(i).x == _Line_Up_Pos_5.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_5.at(i + 1).y - (0 - _mapPos.y) + 50)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_5.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_5.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_5.at(i).y - (0 - _mapPos.y) + 50) &&
				(_main_pos.y >= _Line_Up_Pos_5.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_5.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	for (int i = 0; i < _Line_Up_Pos_6.size() - 1; i++) { // -1 vi cai cuoi + 1 null
		Vec2 _main_pos = main_charactor->GetSprite()->getPosition();
		if (_Line_Up_Pos_6.at(i).y == _Line_Up_Pos_6.at(i + 1).y) {
			if ((_main_pos.y >= _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x <= _Line_Up_Pos_6.at(i + 1).x - (0 - _mapPos.x))) {
				main_charactor->GetSprite()->setPosition(_main_pos.x, _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y));
			}
		}

		// doc
		if (_Line_Up_Pos_6.at(i).x == _Line_Up_Pos_6.at(i + 1).x) {
			if ((_main_pos.x <= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.x >= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x) - 10) &&
				(_main_pos.y >= _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y)) &&
				(_main_pos.y <= _Line_Up_Pos_6.at(i + 1).y - (0 - _mapPos.y) + 50)) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_6.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
			else if ((_main_pos.x <= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x) + 10) &&
				(_main_pos.x >= _Line_Up_Pos_6.at(i).x - (0 - _mapPos.x)) &&
				(_main_pos.y <= _Line_Up_Pos_6.at(i).y - (0 - _mapPos.y) + 50) &&
				(_main_pos.y >= _Line_Up_Pos_6.at(i + 1).y - (0 - _mapPos.y))) {
				main_charactor->GetSprite()->setPosition(_Line_Up_Pos_6.at(i).x - (0 - _mapPos.x), _main_pos.y);
			}
		}
	}

	// main vs rock
	auto size = main_charactor->GetSprite()->getContentSize();
	auto sizeRock = rocks.at(0)->GetSprite()->getContentSize();
	for (int i = 0; i < rocks.size(); i++) {
		auto mainPos = main_charactor->GetSprite()->getPosition() - Vec2(size.width / 2, 0);
		auto rockPos = rocks.at(i)->GetSprite()->getPosition();
		if ((mainPos.x) >= (rockPos.x - (0 - _mapPos.x)) && (mainPos.x) <= (rockPos.x - (0 - _mapPos.x) + sizeRock.width)) {
			log("hehe");
			if (mainPos.y >= rockPos.y - (0 - _mapPos.y) + sizeRock.height - 10 && mainPos.y <= rockPos.y - (0 - _mapPos.y) + sizeRock.height + 5) {
				main_charactor->GetSprite()->setPosition(main_charactor->GetSprite()->getPosition().x, rockPos.y + sizeRock.height);
				log("haha");
				//break;
			}
		}
	}
}

cocos2d::Sprite* mPauseLayer;
cocos2d::Sprite* mHeader;
cocos2d::ui::Button *mBump;
cocos2d::ui::Button *btnPause;

Scene *GamePlay::createGame()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//scene->getPhysicsWorld()->setSubsteps(8);

	// 'layer' is an autorelease object
	auto layer = GamePlay::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool GamePlay::init()
{
	//Create background music
	if (ControlMusic::GetInstance()->isMusic())
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic("Sounds/angkor_wat.mp3", true);
	}

	//Create Map
	CreateMap();

	// initial physics for map
	InitialPhysics();

	// initial state
	InitialState();

	// initial object
	InitialObject();

	// add dispatcher
	AddDispatcher();

	// add button
	InitialButton();

	//create pause layer
	createPauseLayer();

	//Create Joystick
	CreateJoystick(this);

	// update
	scheduleUpdate();

	// create fire
	fire_normal_1 = new Fire(this);
	((Fire*)(fire_normal_1))->setAI(false);
	((Fire*)(fire_normal_1))->setPos(Fire_Normal_1, _tileMap, AI_View);

	fire_normal_2 = new Fire(this);
	((Fire*)(fire_normal_2))->setAI(false);
	((Fire*)(fire_normal_2))->setPos(Fire_Normal_2, _tileMap, AI_View);

	fire_normal_3 = new Fire(this);
	((Fire*)(fire_normal_3))->setAI(false);
	((Fire*)(fire_normal_3))->setPos(Fire_Normal_3, _tileMap, AI_View);

	fire_ai_1 = new Fire(this);
	((Fire*)(fire_ai_1))->setAI(true);
	((Fire*)(fire_ai_1))->setPos(Fire_AI_1, _tileMap, AI_View);

	return true;
}

void GamePlay::CreateMap()
{
	_tileMap = new CCTMXTiledMap();
	_tileMap->initWithTMXFile("map.tmx");
	_background = _tileMap->layerNamed("Background");
	_wall = _tileMap->layerNamed("MapLv1");
	_phy = _tileMap->layerNamed("physics");
	_phy->setVisible(false);
	mObjectGroup = _tileMap->getObjectGroup("Objects");

	mObjects_line_down = _tileMap->getObjectGroup("Line_Down");
	mObjects_line_up = _tileMap->getObjectGroup("Line_Up");
	mObjectFire = _tileMap->getObjectGroup("Fire");


	this->addChild(_tileMap);
}

void GamePlay::InitialState()
{
	// initial number diamon
	this->numDiamond = 0;

	// initial state
	fight = false;

	// initial direction
	moveLeft = false;
	moveRight = false;
	moveUp = false;
	moveDown = false;
	jump = false;
	fall = false;
}

void GamePlay::InitialObject()
{
	auto objects = mObjectGroup->getObjects();
	for (int i = 0; i < objects.size(); i++)
	{
		auto object = objects.at(i);

		auto properties = object.asValueMap();
		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1)//Create Charactor
		{
			this->main_charactor = new MainCharactor(this);
			this->main_charactor->GetSprite()->setPosition(Vec2(posX, posY));
			this->setViewPointCenter(this->main_charactor->GetSprite()->getPosition());
			CreateBloodBar();
			CreateNumDiamon();
		}
		else if (type == 2)//Create Spider
		{
			Spider *spider = new Spider(this);
			spider->GetSprite()->setPosition(Vec2(posX, posY));
			spider->setCatogory(true);
			spiders.push_back(spider);
		}
		else if (type == 4) {//Create Glass
			Objject* glass = new Glass(this);
			glass->GetSprite()->setPosition(Vec2(posX, posY));
			glasss.push_back(glass);
		}
		else if (type == 5) {//Create Diamond
			Objject* diamon = new Diamond(this);
			diamon->GetSprite()->setPosition(Vec2(posX, posY));
			diamons.push_back(diamon);
		}
		else if (type == 6) {//Create Rock
			Objject* rock = new Rock(this);
			rock->GetSprite()->setPosition(Vec2(posX, posY));
			rocks.push_back(rock);
		}
	}


	// get object line down
	auto objects_line_down = mObjects_line_down->getObjects();
	for (int i = 0; i < objects_line_down.size(); i++) {
		auto object = objects_line_down.at(i);
		auto properties = object.asValueMap();

		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1) {
			_Line_Down_Pos.push_back(Vec2(posX, posY));
		}
		else if (type == 2) {
			_Line_Down_Pos_2.push_back(Vec2(posX, posY));
		}
		else if (type == 3) {
			_Line_Down_Pos_3.push_back(Vec2(posX, posY));
		}
		else if (type == 4) {
			_Line_Down_Pos_4.push_back(Vec2(posX, posY));
		}
		else if (type == 5) {
			_Line_Down_Pos_5.push_back(Vec2(posX, posY));
		}
		else if (type == 6) {
			_Line_Down_Pos_6.push_back(Vec2(posX, posY));
		}
	}

	// get object line up
	auto objects_line_up = mObjects_line_up->getObjects();
	for (int i = 0; i < objects_line_up.size(); i++) {
		auto object = objects_line_up.at(i);
		auto properties = object.asValueMap();

		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1) {
			_Line_Up_Pos_1.push_back(Vec2(posX, posY));
		}
		if (type == 2) {
			_Line_Up_Pos_2.push_back(Vec2(posX, posY));
		}
		if (type == 3) {
			_Line_Up_Pos_3.push_back(Vec2(posX, posY));
		}
		if (type == 4) {
			_Line_Up_Pos_4.push_back(Vec2(posX, posY));
		}
		if (type == 5) {
			_Line_Up_Pos_5.push_back(Vec2(posX, posY));
		}
		if (type == 6) {
			_Line_Up_Pos_6.push_back(Vec2(posX, posY));
		}
	}

	// get object fire
	auto objects_fire = mObjectFire->getObjects();
	for (int i = 0; i < objects_fire.size(); i++) {
		auto object = objects_fire.at(i);
		auto properties = object.asValueMap();

		float posX = properties.at("x").asFloat();
		float posY = properties.at("y").asFloat();
		int type = object.asValueMap().at("type").asInt();

		if (type == 1) {
			Fire_Normal_1.push_back(Vec2(posX, posY));
		}else if(type == 2) {
			Fire_AI_1.push_back(Vec2(posX, posY));
		}
		else if (type == 3) {
			Fire_Normal_2.push_back(Vec2(posX, posY));
		}
		else if (type == 4) {
			Fire_dragon_1.push_back(Vec2(posX, posY));
		}
		else if (type == 5) {
			AI_View = Vec2(posX, posY);
		}
		else if (type == 6) {
			Fire_Normal_3.push_back(Vec2(posX, posY));
		}
	}
}

void GamePlay::AddDispatcher()
{
	// key board
	auto keylistener = EventListenerKeyboard::create();
	keylistener->onKeyPressed = CC_CALLBACK_2(GamePlay::OnKeyPressed, this);
	keylistener->onKeyReleased = CC_CALLBACK_2(GamePlay::OnKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keylistener, this);


	// listener contact
	auto contacListener = EventListenerPhysicsContact::create();
	contacListener->onContactBegin = CC_CALLBACK_1(GamePlay::OnContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contacListener, this);

	// touch
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches(true);
	touchListener->onTouchBegan = CC_CALLBACK_2(GamePlay::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GamePlay::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GamePlay::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GamePlay::InitialButton()
{
	//Button Fight
	mBump = ui::Button::create("Button/hammer_normal.png", "Button/hammer_pressed.png");
	mBump->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 180, 100));
	mBump->addTouchEventListener(CC_CALLBACK_2(GamePlay::Fight, this));
	addChild(mBump);

	//Button Pause
	btnPause = ui::Button::create("Button/pause_norrmal.png", "Button/pause_pressed.png");
	btnPause->setAnchorPoint(Vec2(1, 1));
	btnPause->setPosition(Director::getInstance()->getVisibleSize() - Size(3, 8));
	btnPause->addTouchEventListener(CC_CALLBACK_2(GamePlay::Pause, this));
	addChild(btnPause, 2);
}

void GamePlay::InitialPhysics()
{
	// ground
	Size layerSize = _phy->getLayerSize();
	for (int i = 0; i < layerSize.width; i++)
	{
		for (int j = 0; j < layerSize.height; j++)
		{
			auto tileSet = _phy->getTileAt(Vec2(i, j));
			if (tileSet != NULL)
			{
				auto physic = PhysicsBody::createBox(tileSet->getContentSize(), PhysicsMaterial(1.0f, 0.0f, 1.0f));
				physic->setCollisionBitmask(1);
				physic->setContactTestBitmask(true);
				physic->setDynamic(false);
				physic->setMass(100);
				tileSet->setPhysicsBody(physic);
				tileSet->setTag(TAG_MAP);
			}
		}
	}
}

bool GamePlay::OnContactBegin(PhysicsContact &contact)
{
	//auto audio = SimpleAudioEngine::getInstance();

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		// charactor vs spider
		if (nodeA->getTag() == TAG_SPIDER && nodeB->getTag() == TAG_CHARACTOR)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 25);
			//audio->playEffect("Sounds/sfx_character_damage.mp3", false, 1.0f, 1.0f, 1.0f);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_damage.mp3", false);
			}
			((MainCharactor *)(main_charactor))->Stun();
			if (this->main_charactor->GetBlood() <= 0)
			{
				log("die");
				if (ControlMusic::GetInstance()->isSound())
				{
					SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_die.mp3", false);
				}
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenu::createScene()));
			}
		}
		else if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_SPIDER)
		{
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 25);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_damage.mp3", false);
			}
			((MainCharactor *)(main_charactor))->Stun();
			if (this->main_charactor->GetBlood() <= 0)
			{
				log("die");
				if (ControlMusic::GetInstance()->isSound())
				{
					SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_die.mp3", false);
				}
				Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenu::createScene()));
			}
		}


		// main charactor vs diamond
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_DIAMOND)
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_ui_diamond_impact.mp3", false);
			}
			numDiamond++;
			nodeB->removeFromParentAndCleanup(true);
			//nodeB->setVisible(false);
		}
		else if (nodeA->getTag() == TAG_DIAMOND && nodeB->getTag() == TAG_CHARACTOR)
		{
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_ui_diamond_impact.mp3", false);
			}
			numDiamond++;
			nodeA->removeFromParentAndCleanup(true);
			//nodeA->setVisible(false);
		}

		// main charactor vs glass
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_GLASS) {
			nodeB->removeFromParentAndCleanup(true);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_into_bush.mp3", false);
			}
		}
		else if (nodeA->getTag() == TAG_GLASS && nodeB->getTag() == TAG_CHARACTOR) {
			nodeA->removeFromParentAndCleanup(true);
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_into_bush.mp3", false);
			}
		}

		// main charactor vs rock
		auto sizeMain = main_charactor->getSize();
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_ROCK) {
			/*if (nodeA->getPosition().y + sizeMain.height < nodeB->getPosition().y) {
				main_charactor->SetBlood(main_charactor->GetBlood() - 10);
			}*/
			log("cham");
		}
		else if (nodeA->getTag() == TAG_ROCK && nodeB->getTag() == TAG_CHARACTOR) {
			/*if (nodeB->getPosition().y + sizeMain.height < nodeA->getPosition().y) {
				main_charactor->SetBlood(main_charactor->GetBlood() - 10);
			}*/
			log("cham1");
		}

		// main charactor vs fire
		if (nodeA->getTag() == TAG_CHARACTOR && nodeB->getTag() == TAG_FIRE) {
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 20);
		}
		else if (nodeA->getTag() == TAG_FIRE && nodeB->getTag() == TAG_CHARACTOR) {
			this->main_charactor->SetBlood(this->main_charactor->GetBlood() - 20);
		}

		// fight
		if (nodeA->getTag() == TAG_FIGHT && nodeB->getTag() == TAG_ROCK) {
			log("fight1");
		}
		else if (nodeA->getTag() == TAG_ROCK && nodeB->getTag() == TAG_FIGHT) {
			log("fight2");
		}
	}

	return true;
}

void GamePlay::CreateBloodBar()
{
	auto posY = Director::getInstance()->getVisibleSize().height;

	mHeader = Sprite::create("header.png");
	mHeader->setFlippedX(true);
	mHeader->setAnchorPoint(Vec2(1, 1));
	mHeader->setPosition(Director::getInstance()->getVisibleSize());
	mHeader->setVisible(true);
	addChild(mHeader, 2);

	Layer *layer_1 = Layer::create();
	bloodBar_1 = ui::LoadingBar::create("Load/bloodbar_bg.png");
	bloodBar_1->setDirection(ui::LoadingBar::Direction::RIGHT);
	bloodBar_1->setPercent(100);
	bloodBar_1->setPosition(Director::getInstance()->getVisibleSize() - Size(230, 30));

	bloodBar_2 = ui::LoadingBar::create("Load/bloodbar.png");
	bloodBar_2->setDirection(ui::LoadingBar::Direction::LEFT);
	bloodBar_2->setPercent(this->main_charactor->GetBlood());
	bloodBar_2->setPosition(bloodBar_1->getPosition());

	this->addChild(bloodBar_1,3);
	this->addChild(bloodBar_2,2);
}

void GamePlay::CreateNumDiamon()
{
	// sprite diamon
	auto NumDiamon = ResourceManager::GetInstance()->GetSpriteById(3);
	NumDiamon->setScale(0.35);
	NumDiamon->setPosition(bloodBar_2->getPosition() - Vec2(250, 0));
	this->addChild(NumDiamon, 2);

	// label number
	CCString *num = CCString::createWithFormat("%i/30", numDiamond);
	LabelNumDiamon = Label::createWithTTF(num->getCString(), "fonts/Marker Felt.ttf", 30);
	LabelNumDiamon->setPosition(NumDiamon->getPosition() + Vec2(50, 0));
	this->addChild(LabelNumDiamon, 2);
}

void GamePlay::createPauseLayer()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//create pause layer
	mPauseLayer = Sprite::create("pause.png");
	mPauseLayer->setPosition(visibleSize / 2);
	mPauseLayer->setContentSize(visibleSize);
	mPauseLayer->setVisible(false);
	addChild(mPauseLayer, 2);

	//Button Go to Map
	auto btnHome = ui::Button::create("Button/home_normal.png", "Button/home_pressed.png");
	btnHome->setScale(SCALE_BUTTON);
	btnHome->setPosition(Vec2(visibleSize / 2 - Size(0, 80)));
	btnHome->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, MainMenu::createScene()));
	});
	mPauseLayer->addChild(btnHome);

	//Button Restart
	auto btnRestart = ui::Button::create("Button/restart_normal.png", "Button/restart_pressed.png");
	btnRestart->setScale(SCALE_BUTTON);
	btnRestart->setPosition(btnHome->getPosition() + Size(0, 70));
	btnRestart->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
	});
	mPauseLayer->addChild(btnRestart);

	//Button Resume
	auto btnResume = ui::Button::create("Button/resume_normal.png", "Button/resume_pressed.png");
	btnResume->setScale(SCALE_BUTTON);
	btnResume->setPosition(btnRestart->getPosition() + Size(0, 70));
	btnResume->addClickEventListener([](Ref* event) {
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
		}
		SimpleAudioEngine::getInstance()->resumeAllEffects();
		SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
		Director::getInstance()->resume();
		btnPause->setVisible(true);
		mBump->setVisible(true);
		mPauseLayer->setVisible(false);
	});
	mPauseLayer->addChild(btnResume);
}

void GamePlay::push_rock()
{
	push = false;
	int index = -1;
	index = check_push();
	if (index != -1 && index != -2) {
		push = true;
		SPEED_CHARACTOR_RUN = 5;

		Size size_rock = rocks.at(0)->GetSprite()->getContentSize();
		Vec2 p_rock = rocks.at(index)->GetSprite()->getPosition() + Vec2(size_rock.width / 2, 0);
		Vec2 p_main = main_charactor->GetSprite()->getPosition();
		
		if (p_main.x > p_rock.x) {
			//log("cham phai");
			rocks.at(index)->GetSprite()->setPosition(rocks.at(index)->GetSprite()->getPosition() -
					Vec2(SPEED_CHARACTOR_RUN, 0));
		}
		else if (p_main.x < p_rock.x) {
			//log("cham trai");
			rocks.at(index)->GetSprite()->setPosition(rocks.at(index)->GetSprite()->getPosition() +
						Vec2(SPEED_CHARACTOR_RUN, 0));
		}

		((MainCharactor*)(main_charactor))->Push();
	}
	else if (index == -2) {
		SPEED_CHARACTOR_RUN = 0;
	}
	else {
		SPEED_CHARACTOR_RUN = 5;
	}
}

int GamePlay::check_push()
{
	int index = -1;
	Size size_rock = rocks.at(0)->GetSprite()->getContentSize();
	Vec2 p_main = main_charactor->GetSprite()->getPosition();
	Vec2 p_rock = rocks.at(0)->GetSprite()->getPosition() + Vec2(size_rock.width / 2, 0);
	
	float min_horizontal = 1000000;

	float _dis_horizontal = main_charactor->getSize().width / 2 + size_rock.width / 2;

	for (int i = 0; i < rocks.size(); i++) {
		auto r = rocks.at(i)->GetSprite()->getPosition() + Vec2(size_rock.width / 2, 0);
		float dis = distance(p_main.x, r.x);
		if (dis < min_horizontal && (p_main.y >= r.y - 10 && p_main.y <= r.y + size_rock.height - 10)) {
			min_horizontal = dis;
			index = i;
		}
	}

	if (index != -1) {
		p_rock = rocks.at(index)->GetSprite()->getPosition() + Vec2(size_rock.width / 2, 0);
		float dis = distance(p_main.x, p_rock.x);
		if (dis <= _dis_horizontal && !check_Collision(index)) {
			// da khong cham nhau
			//log("cham cham");
			return index;
		}
		else if (dis <= _dis_horizontal && check_Collision(index)) {
			// da cham nhau
			//log("return -2");
			return -2;
		}
	}

	return -1;
}

bool GamePlay::check_Collision(int index)
{
	Size size = rocks.at(0)->GetSprite()->getContentSize();
	auto rock_1 = rocks.at(index)->GetSprite()->getPosition();
	for (int j = 0; j < rocks.size(); j++) {
		auto rock_2 = rocks.at(j)->GetSprite()->getPosition();
		if (j != index && rock_1.y >= rock_2.y - 5 && rock_1.y <= rock_2.y + size.height) {
			if (rock_1.x >= rock_2.x + size.width - 5 && rock_1.x <= rock_2.x + size.width + 5 ||
				rock_1.x >= rock_2.x - size.width - 5 && rock_1.x <= rock_2.x - size.width + 5) {
				return true;
			}
		}
	}

	return false;
}

float GamePlay::distance_1(float p_1, float p_2)
{
	return p_1 - p_2;
}

float GamePlay::distance(float main, float rock)
{
	//Vec2 P_main = main->GetSprite()->getPosition();
	//Vec2 P_rock = rock->GetSprite()->getPosition();

	//float dis = sqrt((P_main.x - P_rock.x)*(P_main.x - P_rock.x) + (P_main.y - P_rock.y)*(P_main.y - P_rock.y));
	float dis = abs(main - rock);

	return dis;
}

void GamePlay::Fight(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::BEGAN:
	{
		if (ControlMusic::GetInstance()->isSound())
		{
			SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_character_icehammer.mp3", false);
		}
		fight = true;
		break;
	}
	case ui::Widget::TouchEventType::ENDED:
		fight = false;
		break;
	}
}

void GamePlay::Pause(cocos2d::Ref * sender, cocos2d::ui::Widget::TouchEventType type)
{
	switch (type)
	{
	case ui::Widget::TouchEventType::ENDED:
		auto funcPause = CallFunc::create([]() {
			if (ControlMusic::GetInstance()->isSound())
			{
				SimpleAudioEngine::getInstance()->playEffect("Sounds/sfx_clickbutton.mp3", false);
			}
			Director::getInstance()->pause();
			//SimpleAudioEngine::getInstance()->pauseAllEffects();
			SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
		});
		btnPause->setVisible(false);
		mBump->setVisible(false);
		mPauseLayer->setOpacity(0);
		mPauseLayer->setVisible(true);
		auto fadeIn = FadeIn::create(0.3f);
		mPauseLayer->runAction(Sequence::create(fadeIn, funcPause, nullptr));
		break;
	}
}

void GamePlay::update(float deltaTime)

{
	// update main charactor
	main_charactor->Update(deltaTime);
	((MainCharactor *)main_charactor)->setState(fight, moveLeft, moveRight, jump, stun, push);

	// set view
	this->setViewPointCenter(main_charactor->GetSprite()->getPosition());

	// update blood
	bloodBar_2->setPercent(this->main_charactor->GetBlood());

	// update number diamond
	CCString *num = CCString::createWithFormat("%i/30", numDiamond);
	LabelNumDiamon->setString(num->getCString());

	// push rock
	push_rock();

	// collision vs ground
	checkGround_2();

	// update fire AI
	fire_ai_1->Update(deltaTime);
	((Fire*)(fire_ai_1))->setPosMain(this->main_charactor->GetSprite()->getPosition());

	//Update Joystick
	UpdateJoystick(deltaTime);
}

void GamePlay::setViewPointCenter(CCPoint position)
{
	CCSize winSize = Director::getInstance()->getVisibleSize();

	Vec2 mapMoveDistance = Vec2(0, 0);
	Vec2 mcMoveDistance = Vec2(0, 0);
	if (moveRight)
	{
		if (main_charactor->GetSprite()->getPosition().x < winSize.width / 2)
		{
			mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		else
		{
			float mapWidth = _tileMap->getMapSize().width * _tileMap->getTileSize().width;
			if (_tileMap->getPosition().x > -(mapWidth - winSize.width - SPEED_CHARACTOR_RUN))
			{
				mapMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
			}
			else if (main_charactor->GetSprite()->getPosition().x <= (winSize.width - SPEED_CHARACTOR_RUN))
			{
				mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
			}
		}

		//main_charactor->GetSprite()->getPhysicsBody()->setVelocity(Vec2(150, 0));
	}
	else if (moveLeft)
	{
		//main_charactor->GetSprite()->getPhysicsBody()->setVelocity(Vec2(-150, 0));
		if (main_charactor->GetSprite()->getPosition().x > winSize.width / 2)
		{
			mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		else
		{
			if (_tileMap->getPosition().x <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
			}
			else if (main_charactor->GetSprite()->getPosition().x >= SPEED_CHARACTOR_RUN)
			{
				mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
			}
		}
	}
	else if (moveUp || jump)
	{
		//main_charactor->GetSprite()->getPhysicsBody()->applyImpulse(Vec2(0, 7000));
		if (main_charactor->GetSprite()->getPosition().y < winSize.height / 2)
		{
			mcMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN + 5);
		}
		else
		{
			float mapHeight = _tileMap->getMapSize().height * _tileMap->getTileSize().height;
			if (_tileMap->getPosition().y > -(mapHeight - winSize.height - SPEED_CHARACTOR_RUN + 5))
			{
				mapMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN + 5);
			}
			else if (main_charactor->GetSprite()->getPosition().y <= (winSize.height))
			{
				mcMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN + 5);
			}
		}
	}
	else if (moveDown)
	{
		if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
		{
			mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
		}
		else
		{
			if (_tileMap->getPosition().y <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
			}
			else if (main_charactor->GetSprite()->getPosition().y >= SPEED_CHARACTOR_RUN)
			{
				mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
			}
		}
	}
	else if (main_charactor->GetSprite()->getPosition().y < Director::getInstance()->getWinSize().height / 2 &&
		_tileMap->getPosition().y < 0) {
		if (main_charactor->GetSprite()->getPosition().y > winSize.height / 2)
		{
			//mcMoveDistance = -Vec2(0, SPEED_CHARACTOR_RUN);
		}
		else
		{
			if (_tileMap->getPosition().y <= -SPEED_CHARACTOR_RUN)
			{
				mapMoveDistance = Vec2(0, SPEED_CHARACTOR_RUN);
			}
		}
		if (moveLeft) {
			mcMoveDistance = -Vec2(SPEED_CHARACTOR_RUN, 0);
		}
		if (moveRight) {
			mcMoveDistance = Vec2(SPEED_CHARACTOR_RUN, 0);
		}
	}

	if (mcMoveDistance != Vec2(0, 0))
	{
		main_charactor->GetSprite()->setPosition(main_charactor->GetSprite()->getPosition() + mcMoveDistance);
	}

	if (mapMoveDistance != Vec2(0, 0))
	{
		// update map
		_tileMap->setPosition(_tileMap->getPosition() + mapMoveDistance);

		// update spider
		for (int i = 0; i < spiders.size(); i++)
		{
			spiders.at(i)->GetSprite()->setPosition(spiders.at(i)->GetSprite()->getPosition() + mapMoveDistance);
		}

		// update glass
		for (int i = 0; i < glasss.size(); i++)
		{
			glasss.at(i)->GetSprite()->setPosition(glasss.at(i)->GetSprite()->getPosition() + mapMoveDistance);
		}

		// update diamon
		for (int i = 0; i < diamons.size(); i++)
		{
			diamons.at(i)->GetSprite()->setPosition(diamons.at(i)->GetSprite()->getPosition() + mapMoveDistance);
		}

		// update rock
		for (int i = 0; i < rocks.size(); i++)
		{
			rocks.at(i)->GetSprite()->setPosition(rocks.at(i)->GetSprite()->getPosition() + mapMoveDistance);
		}
	}
}

void GamePlay::CreateJoystick(Layer * layer)
{
	auto thumb = Sprite::create("thumb.png");
	auto joystick = Sprite::create("joystick.png");
	Rect joystickBaseDimensions = Rect(0, 0, 40.f, 40.0f);
	Point joystickBasePosition;
	joystickBasePosition = Vec2(MARGIN_JOYSTICK + thumb->getBoundingBox().size.width / 2 + joystick->getBoundingBox().size.width / 2
		, MARGIN_JOYSTICK + thumb->getBoundingBox().size.height / 2 + joystick->getBoundingBox().size.height / 2);

	joystickBase = new SneakyJoystickSkinnedBase();
	joystickBase->init();
	joystickBase->setPosition(Vec2(100,100));
	joystickBase->setBackgroundSprite(thumb);
	joystickBase->setAnchorPoint(Vec2(0, 0));
	joystickBase->setThumbSprite(joystick);
	joystickBase->getThumbSprite()->setScale(0.2f);
	joystickBase->setScale(1.0f);
	joystick->setScale(0.5f);
	SneakyJoystick *aJoystick = new SneakyJoystick();
	aJoystick->initWithRect(joystickBaseDimensions);
	aJoystick->autorelease();
	joystickBase->setJoystick(aJoystick);
	joystickBase->setPosition(Vec2(100,100));

	leftJoystick = joystickBase->getJoystick();
	activeRunRange = thumb->getBoundingBox().size.height / 2;
	layer->addChild(joystickBase);
}

void GamePlay::UpdateJoystick(float dt)
{

	Point pos = leftJoystick->getStickPosition();
	float radius = std::sqrt(pos.x*pos.x + pos.y*pos.y);
	if (radius > 0)
	{
		float degree = std::atan2f(pos.y, pos.x) * 180 / 3.141593;
		if (degree > 135 && degree < 180 || degree > -180 && degree < -135)//MoveLeft
		{
			moveRight = false;
			moveLeft = true;
			moveUp = false;
			moveDown = false;
		}
		if (degree > -135 && degree < -45 )//Move Down
		{
			moveRight = false;
			moveLeft = false;
			moveUp = false;
			moveDown = true;
		}
		if (degree > -45 && degree < 45)//Move Right
		{
			moveRight = true;
			moveLeft = false;
			moveUp = false;
			moveDown = false;
		}
		if (degree > 45 && degree < 135)//Move Up
		{
			moveRight = false;
			moveLeft = false;
			moveUp = true;
			moveDown = false;
		}
	}
	else
	{
		moveRight = false;
		moveLeft = false;
		moveUp = false;
		moveDown = false;
	}
}

GamePlay::GamePlay()
{
}

GamePlay::~GamePlay()
{
}

bool GamePlay::onTouchBegan(Touch * touch, Event * event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::BEGAN;
	mCurrentTouchPoint = touch->getLocation();
	return true;
}

void GamePlay::onTouchMoved(Touch * touch, Event * event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::MOVED;
	mCurrentTouchPoint = touch->getLocation();
	//log("Touch Moved (%f, %f)", touch->getLocation().x, touch->getLocation().y);
}

void GamePlay::onTouchEnded(Touch * touch, Event * event)
{
	mCurrentTouchState = ui::Widget::TouchEventType::ENDED;
	mCurrentTouchPoint = Point(-1, -1);
}

void GamePlay::OnKeyPressed(EventKeyboard::KeyCode keycode, Event * event)
{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_Q:
	{
		if (moveLeft || moveRight)
		{
			fight = false;
		}
		else
		{
			fight = true;
		}

		break;
	}

	case EventKeyboard::KeyCode::KEY_A:
	{
		moveLeft = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		moveRight = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_W:
	{
		moveUp = true;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		moveDown = true;
		break;
	}
	default:
		break;
	}
}

void GamePlay::OnKeyReleased(EventKeyboard::KeyCode keycode, Event * event)

{
	switch (keycode)
	{
	case EventKeyboard::KeyCode::KEY_Q:
	{
		fight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_A:
	{
		moveLeft = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_D:
	{
		moveRight = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_W:
	{
		moveUp = false;
		break;
	}
	case EventKeyboard::KeyCode::KEY_S:
	{
		moveDown = false;
		break;
	}
	default:
		break;
	}
}