#ifndef bsp_h
#define bsp_h

#define BSP_TICKS_PER_SEC    1000U

void BSP_init(void);

void BSP_show_screen(enum_t screen);

enum UiSignals {
	UI_LOGIN = 100,
	UI_CHARACTER_CREATE,
	UI_CHARACTER_SELECT,
	UI_IN_GAME
};

typedef struct UiCharacterTag {

	unsigned int character_id;

	size_t character_name_size;
	char* character_name;

} UiCharacterData;

typedef struct UiUserTag {

	unsigned int user_id;

	size_t username_size;
	char* username;

	size_t password_size;
	char* password;

	size_t n_characters;
	UiCharacterData* characters;

} UiUserData;

typedef struct UiInGameTag {

	UiCharacterData character;

} UiInGameData;

void const BSP_set_character_data(UiCharacterData data);
void const BSP_set_user_data(UiUserData data);
void const BSP_set_in_game_data(UiInGameData data);

#endif /* bsp_h */
