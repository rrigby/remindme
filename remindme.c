#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libnotify/notify.h>
#include <unistd.h>

#define MAX_MSG_LEN 512

// Function to concat words and
// place a space between them
char* wordcat(size_t* s, size_t n, char* dest, char* src)
{
    *s = 0;
    while (*dest) ++dest;
    while (*dest++ = *src++) {
        if(*s == n) {
           break;
       }
       (*s)++;
     }
    *(--dest) = ' ';
    *(++dest) = '\0';
    return dest;
}

int modifier(char m)
{
    switch (m) {
        case 's': return 1;
        case 'm': return 60;
        case 'h': return 3600;
        case 'd': return 86400;
        default: return 0;
    }
}

int main(int argc, char* argv[])
{
    char* message = NULL;
    char m = 0;
    unsigned int l = 0;
    gboolean success;
    GError* error = NULL;
    NotifyNotification* notification = NULL;

    if (argc < 3) {
        printf("Please provide proper arguments.\n");
        return 0;
    } else if (argc >= 3) {
        message = calloc(MAX_MSG_LEN, sizeof(char));
        char *p = message;
        size_t message_length = 0;
        size_t size = 0;
        for(int i = 1; i < argc-1; ++i) {
            p = wordcat(&size, MAX_MSG_LEN-message_length, p, argv[i]);
            message_length += size;
        }
        sscanf(argv[argc-1], "%d%c", &l,&m);
    }
    printf("MSG: %s, L: %d, M: %c\n",message,l,m);

    success = notify_init(argv[0]);
    if(!success) {
        fprintf(stderr, "notify_init() failed. Exiting.\n");
        return 0;
    }

    notification = notify_notification_new("remindMe", message, NULL);
    notify_notification_set_timeout(notification,NOTIFY_EXPIRES_NEVER);
    sleep(l*modifier(m));

    success = notify_notification_show(notification, &error);
    if(!success) {
        fprintf(stderr, "%s\n", error->message);
        g_clear_error (&error);
    }
    notify_uninit();
    free(message);
    return 0;
}
