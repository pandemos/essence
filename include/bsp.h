#ifndef bsp_h
#define bsp_h

#define BSP_TICKS_PER_SEC    1000U

#include "model/model_user.h"
#include "model/model_vessel.h"
#include "model/model_user_vessel.h"

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

// Data model support
void BSP_data_create_user_table();
void BSP_data_create_user(ModelUser* user);
void BSP_data_get_user(unsigned int user_id, ModelUser* model);
void BSP_data_update_user(ModelUser* user);
void BSP_data_delete_user(unsigned int user_id);
void BSP_data_search_users(const char* col_to_search, const char* value);
void BSP_data_user_exists(unsigned int user_id);

void BSP_data_create_vessel_table();
void BSP_data_create_vessel(ModelVessel* vessel);
void BSP_data_get_vessel(unsigned int vessel_id);
void BSP_data_update_vessel(ModelVessel* vessel);
void BSP_data_delete_vessel(unsigned int vessel_id);
void BSP_data_search_vessels(const char* col_to_search, const char* value);
void BSP_data_vessel_exists(unsigned int vessel_id);

void BSP_data_create_user_vessel_table();
void BSP_data_set_user_vessel(unsigned int user_id, unsigned int vessel_id);
void BSP_data_count_user_vessels(unsigned int user_id);
void BSP_data_get_user_vessels(unsigned int user_id);
void BSP_data_unset_user_vessel(unsigned int user_id, unsigned int vessel_id);

#endif /* bsp_h */
