#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

// Priorities (lower = higher priority)
#define KEYBOARD_PRIORITY 1
#define MOUSE_PRIORITY    2
#define PRINTER_PRIORITY  3

// Mask flags (true = enabled)
bool keyboard_enabled = true;
bool mouse_enabled = true;
bool printer_enabled = true;

pthread_mutex_t lock;

void handle_interrupt(const char* device, int priority) {
    pthread_mutex_lock(&lock);
    printf("%s Interrupt Triggered -> Handling ISR...\n", device);
    sleep(1); // simulate ISR delay
    printf("%s Interrupt -> Completed\n", device);
    pthread_mutex_unlock(&lock);
}

void* keyboard_thread(void* arg) {
    while (1) {
        sleep(rand() % 3 + 1);
        if (keyboard_enabled)
            handle_interrupt("Keyboard", KEYBOARD_PRIORITY);
        else
            printf("Keyboard Interrupt Ignored (Masked)\n");
    }
}

void* mouse_thread(void* arg) {
    while (1) {
        sleep(rand() % 4 + 2);
        if (mouse_enabled)
            handle_interrupt("Mouse", MOUSE_PRIORITY);
        else
            printf("Mouse Interrupt Ignored (Masked)\n");
    }
}

void* printer_thread(void* arg) {
    while (1) {
        sleep(rand() % 5 + 3);
        if (printer_enabled)
            handle_interrupt("Printer", PRINTER_PRIORITY);
        else
            printf("Printer Interrupt Ignored (Masked)\n");
    }
}

void* user_input_thread(void* arg) {
    char command[20];
    while (1) {
        printf("\nEnter command (mask/unmask/exit): ");
        scanf("%s", command);

        if (strcmp(command, "mask") == 0) {
            printf("Enter device (keyboard/mouse/printer): ");
            scanf("%s", command);
            if (strcmp(command, "keyboard") == 0) keyboard_enabled = false;
            else if (strcmp(command, "mouse") == 0) mouse_enabled = false;
            else if (strcmp(command, "printer") == 0) printer_enabled = false;
            printf("%s interrupts masked\n", command);
        }
        else if (strcmp(command, "unmask") == 0) {
            printf("Enter device (keyboard/mouse/printer): ");
            scanf("%s", command);
            if (strcmp(command, "keyboard") == 0) keyboard_enabled = true;
            else if (strcmp(command, "mouse") == 0) mouse_enabled = true;
            else if (strcmp(command, "printer") == 0) printer_enabled = true;
            printf("%s interrupts unmasked\n", command);
        }
        else if (strcmp(command, "exit") == 0) {
            printf("Exiting simulation...\n");
            exit(0);
        }
    }
}

int main() {
    srand(time(NULL));
    pthread_t t_keyboard, t_mouse, t_printer, t_user;

    pthread_mutex_init(&lock, NULL);

    pthread_create(&t_keyboard, NULL, keyboard_thread, NULL);
    pthread_create(&t_mouse, NULL, mouse_thread, NULL);
    pthread_create(&t_printer, NULL, printer_thread, NULL);
    pthread_create(&t_user, NULL, user_input_thread, NULL);

    pthread_join(t_user, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
