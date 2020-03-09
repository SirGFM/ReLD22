#include <core/keyboard.h>

SDLKey *_keymap = 0;
int *_keyval = 0;
int _keyNum = 0;
int _didPress = 0;
SDLKey _lastKey;

void CppOGL::Keyboard::init(int keyNum) {
	if (_keymap) {
		delete[] _keymap;
		delete[] _keyval;
	}
	_keymap = new SDLKey[keyNum];
	_keyval = new int[keyNum];
	_keyNum = keyNum;
}

void CppOGL::Keyboard::clear() {
	if (_keymap) {
		delete[] _keymap;
		delete[] _keyval;
	}
	_keymap = 0;
	_keyval = 0;
}

void CppOGL::Keyboard::addKey(int key, SDLKey sym) {
	if (key < 0 || key > _keyNum)
		return;
	_keymap[key] = sym;
	_keyval[key] = 0;
}

void CppOGL::Keyboard::setKey(SDLKey sym, int val) {
	int i = -1;
	while (++i < _keyNum)
		if (_keymap[i] == sym) {
			_keyval[i] = val;
			return;
		}
}

int CppOGL::Keyboard::queryKey(int key) {
	if (key < 0 || key > _keyNum)
		return 0;
	return _keyval[key];
}

SDLKey CppOGL::Keyboard::lastKey() {
	return _lastKey;
}

int CppOGL::Keyboard::gotKeyPress() {
	return _didPress;
}
