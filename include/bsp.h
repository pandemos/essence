#ifndef bsp_h
#define bsp_h

#define BSP_TICKS_PER_SEC    1000U

void BSP_init(void);

void BSP_show_screen(enum_t screen);

enum DataTypes {
	DATA_TYPE_NULL = 0,
	DATA_TYPE_INT,
	DATA_TYPE_STRING
};

enum DataKeys {
	DATA_ROOT = 100,
	DATA_UNKNOWN = 101
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

void BSP_init_ui(void);
void BSP_deactivate_ui(void);
void BSP_set_character_data(UiCharacterData data);
void BSP_set_user_data(UiUserData data);
void BSP_set_in_game_data(UiInGameData data);

// Database support
void BSP_data_init(void);
void BSP_data_deactivate(void);

#endif /* bsp_h */
