#include QMK_KEYBOARD_H
#include "wingb_split_kbd.h"

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)

enum custom_keycodes {
    M_COPY = SAFE_RANGE,
    M_SCR_LOCK
};

// @see https://docs.qmk.fm/#/keycodes_basic
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
        [_QWERTY] = LAYOUT(
            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,              KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,  KC_EQL,
//          _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
            KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,              KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
            KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,              KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,              KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
//          _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
         MO(_LOWER), KC_CAPS, KC_LOPT, KC_LCMD, KC_SPC,  KC_BSPC,           KC_SPC,  KC_ESC,  KC_LBRC, KC_RBRC, KC_LEFT, KC_RGHT,
                                                KC_BSPC, KC_ENT,            KC_ENT,  M(0)
        ),
        [_LOWER] = LAYOUT(
            KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,             KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
//          _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
            KC_ESC,  _______, KC_UP,   _______, _______, _______,           _______, KC_7,    KC_8,    KC_9,    _______, _______,
            _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_LBRC,           KC_RBRC, KC_4,    KC_5,    KC_6,    _______, _______,
            _______, KC_VOLD, KC_VOLU, KC_MUTE, _______, KC_LPRN,           KC_RPRN, KC_1,    KC_2,    KC_3,    _______, _______,
//          _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______,           _______, KC_0,    _______, _______, KC_UP,   KC_DOWN,
                                                _______, _______,           _______, _______
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
                if (get_mods() & MOD_MASK_SHIFT) { //MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
                    // SHIFT+ESC를 '~'키로 정의를 한다.
                    register_code(KC_GRV);
                } else {
                    // ESC만 눌린 경우 ESC키로 정의한다.
                    register_code(KC_ESC);
                }
            } else { // 키보드가 눌리지 않았을 경우 등록된 코드를 풀어준다.
                unregister_code(KC_GRV);
                unregister_code(KC_ESC);
            }

            return false; // 발생한 키 처리를 했으니 false 처리를 하여 중복으로 넘겨주지 않도록 한다.

        case KC_DEL: // SHIFT + DEL키에 INSERT키 대입
            if (record->event.pressed) { // 키보드가 눌렸을 경우
                // 왼쪽 SHIFT키와 오른쪽 SHIFT키가 눌렸는지 확인
                if (get_mods() & MOD_MASK_SHIFT) {
                    // SHIFT+DEL을 INSERT키로 치환하는 것이기 때문에 SHIFT+INSERT가 되지 않게 SHIFT를 빼준다.
                    if (get_mods() & MOD_BIT(KC_LSFT)) unregister_code(KC_LSFT); // Left SHIFT키가 눌렸을 경우 해제한다.
                    if (get_mods() & MOD_BIT(KC_RSFT)) unregister_code(KC_RSFT); // Right SHIFT키가 눌렸을 경우 해제한다.

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

        case M_COPY:
            if (record->event.pressed) {
                register_code(KC_LCMD);

                if (record->tap.count == 1) {
                    register_code(KC_C);
                    unregister_code(KC_C);
                } else if (record->tap.count == 2) {
                    register_code(KC_X);
                    unregister_code(KC_X);
                } else {
                    register_code(KC_C);
                    unregister_code(KC_C);
                };

                unregister_code(KC_LCMD);
            }
            break;

        case M_SCR_LOCK:
            // https://github.com/qmk/qmk_firmware/blob/master/docs/feature_macros.md
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LCMD) "q" SS_DELAY(200) SS_UP(X_LCTL) SS_UP(X_LCMD) SS_UP(X_LCTL));
            return false;

        default:
            return true; // Process all other keycodes normally
    }

    return true; // Process all other keycodes normally
}
