#ifndef UTILS_H_
    #define UTILS_H_

    #include <stdlib.h>
    #include <stdbool.h>
    #include <time.h>

    #define MAX_NAME_LENGTH 32
    #define MAX_DESCRIPTION_LENGTH 255
    #define MAX_BODY_LENGTH 512

enum OP_CODE {
    QUIT,
    LOGIN,
    LOGOUT,
    USERS_REQUEST,
    USERS_RESPONSE,
    USER_REQUEST,
    USER_RESPONSE,
    SEND,
    MESSAGES_REQUEST,
    MESSAGES_RESPONSE,
    MESSAGE_SENT
};

typedef struct {
    char sender_uuid[37];
    time_t message_timestamp;
    char message_body[MAX_BODY_LENGTH];
} message_t;

typedef struct {
    message_t messages[100];
} thread_t;

typedef struct quit {
    size_t len;
    int code;
} quit_t;

typedef struct login {
    size_t len;
    int code;
    char username[MAX_NAME_LENGTH];
} login_t;

typedef struct logout {
    size_t len;
    int code;
} logout_t;

typedef struct users_request {
    size_t len;
    int code;
} users_request_t;

typedef struct users_response {
    size_t len;
    int code;
    char usernames[100][MAX_NAME_LENGTH];
    char usernames_UUID[100][37];
    int username_connection_count[100];
} users_response_t;

typedef struct user_request {
    size_t len;
    int code;
    char UUID[37];
} user_request_t;

typedef struct user_response {
    size_t len;
    int code;
    bool succeeded;
    char username[MAX_NAME_LENGTH];
    char username_UUID[37];
    int connection_count;
} user_response_t;

typedef struct {
    size_t len;
    int code;
    char sender_uuid[37];
    char receiver_uuid[37];
    char message_body[MAX_BODY_LENGTH];
} send_t;

typedef struct {
    thread_t thread;
} messages_t;

typedef struct {
    size_t len;
    int code;
    char sender_uuid[37];
    char receiver_uuid[37];
} messages_request_t;

typedef struct {
    size_t len;
    int code;
    messages_t messages;
} messages_response_t;

typedef struct {
    size_t len;
    int code;
    char uuid[37];
    char message[MAX_BODY_LENGTH];
} message_sent_t;

#endif /* !UTILS_H_ */
