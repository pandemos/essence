#ifndef model_user_h
#define model_user_h

typedef struct {
	unsigned int user_id;

	size_t username_size;
	char username[128];

	size_t password_size;
	char password[128];
} ModelUser;

#endif
