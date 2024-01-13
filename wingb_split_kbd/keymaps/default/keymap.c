#include QMK_KEYBOARD_H
#include "wingB.h"

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_QWERTY] = LAYOUT(
            KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,                  KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_EQL,
//          ___________, ___________, ___________, ___________, ___________, ___________,           ___________, ___________, ___________, ___________, ___________, ___________,
            KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,                  KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_MINS,
            MO(_LOWER),  KC_A,        KC_S,        KC_D,        KC_F,        KC_G,                  KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_QUOT,
            KC_LSFT,     KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,                  KC_B,        KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_SLSH,
            KC_ESC,      KC_LCTL,     KC_CAPS,     KC_LOPT,     KC_LCMD,     KC_SPC,                KC_SPC,      KC_RCMD,     KC_LEFT,     KC_DOWN,     KC_UP,       KC_RGHT ,
//          ___________, ___________, ___________, ___________, ___________, ___________,           ___________, ___________, ___________, ___________, ___________, ___________,
                                                                KC_ENT,      KC_BSPC,               KC_BSPC,     KC_ENT
        ),
        [_LOWER] = LAYOUT(
            ___________, KC_F1,       KC_F2,       KC_F3,       KC_F4        KC_F5  ,               KC_F6,       KC_F7,       KC_F8,      KC_F9,        KC_F10,      KC_F11,
//          ___________, ___________, ___________, ___________, ___________, ___________,           ___________, ___________, ___________, ___________, ___________, ___________,
            ___________, ___________, KC_UP,       ___________, ___________, ___________,           ___________, KC_7,        KC_8,        KC_9,        ___________, ___________,
            ___________, KC_LEFT,     KC_DOWN,     KC_RGHT,     ___________, KC_LBRC,               KC_RBRC,     KC_4,        KC_5,        KC_6,        ___________, ___________,
            ___________, KC_HOME,     KC_PGUP,     KC_PGDN,     ___________, KC_LPRN,               KC_RPRN,     KC_1,        KC_2,        KC_3,        ___________, ___________,
            ___________, ___________, ___________, ___________, ___________, ___________,           ___________, KC_0,        ___________, ___________, ___________, ___________,
//          ___________, ___________, ___________, ___________, ___________, ___________,           ___________, ___________, ___________, ___________, ___________, ___________,
                                                                ___________, ___________,           ___________, ___________,
       )
};

/**
 *
 * @see https://blog.naver.com/skywood1/221822332540
 *
 * @param keycode
 * @param record
 * @return
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_ESC: // SHIFT + ESC키에 '~' 대체
            // 키보드가 눌렸을 경우
            if (record->event.pressed) {
                // 왼쪽 SHIFT키와 오른쪽 SHIFT키가 눌렸는지 확인
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    // SHIFT+ESC를 '~'키로 정의를 한다.
                    register_code(KC_TILD);
                } else {
                    // ESC만 눌린 경우 ESC키로 정의한다.
                    register_code(KC_ESC);
                }
            } else { // 키보드가 눌리지 않았을 경우 등록된 코드를 풀어준다.
                unregister_code(KC_TILD);
                unregister_code(KC_ESC);
            }

            return false; // 발생한 키 처리를 했으니 false 처리를 하여 중복으로 넘겨주지 않도록 한다.

        case KC_DEL: // SHIFT + DEL키에 INSERT키 대입
            if (record->event.pressed) { // 키보드가 눌렸을 경우
                // 왼쪽 SHIFT키와 오른쪽 SHIFT키가 눌렸는지 확인
                if (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT)) {
                    // SHIFT+DEL을 INSERT키로 치환하는 것이기 때문에 SHIFT+INSERT가 되지 않게 SHIFT를 빼준다.
                    if (get_mods() & MOD_BIT(KC_LSHIFT)) unregister_code(KC_LSHIFT); // Left SHIFT키가 눌렸을 경우 해제한다.
                    if (get_mods() & MOD_BIT(KC_RSHIFT)) unregister_code(KC_RSHIFT); // Right SHIFT키가 눌렸을 경우 해제한다.

                    // SHIFT+DEL를 INSERT키로 정의를 한다.
                    register_code(KC_INS);
                } else {
                    // DEL만 눌린 경우 DEL키로 정의한다.
                    register_code(KC_DEL);
                }
            } else { // 키보드가 눌리지 않았을 경우 등록된 코드를 풀어준다.
                unregister_code(KC_INS);
                unregister_code(KC_DEL);
            }
            return false; // 발생한 키 처리를 했으니 false 처리를 하여 중복으로 넘겨주지 않도록 한다.

        default:
            return true; // Process all other keycodes normally
    }
}
