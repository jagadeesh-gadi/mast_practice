
#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

struct signal_entry
{
    int sig;
    const char *name;
};

static volatile sig_atomic_t received_signal = 0;

void handler(int sig, siginfo_t *info, void *context)
{
    (void)info;
    (void)context;

    received_signal = sig;
}

int main(void)
{
    struct signal_entry signals[] = {
        {SIGHUP, "SIGHUP"},
        {SIGINT, "SIGINT"},
        {SIGQUIT, "SIGQUIT"},
        {SIGILL, "SIGILL"},
        {SIGTRAP, "SIGTRAP"},
        {SIGABRT, "SIGABRT"},
        {SIGBUS, "SIGBUS"},
        {SIGFPE, "SIGFPE"},
        {SIGKILL, "SIGKILL"},
        {SIGUSR1, "SIGUSR1"},
        {SIGSEGV, "SIGSEGV"},
        {SIGUSR2, "SIGUSR2"},
        {SIGPIPE, "SIGPIPE"},
        {SIGALRM, "SIGALRM"},
        {SIGTERM, "SIGTERM"},
        {SIGSTKFLT, "SIGSTKFLT"},
        {SIGCHLD, "SIGCHLD"},
        {SIGCONT, "SIGCONT"},
        {SIGSTOP, "SIGSTOP"},
        {SIGTSTP, "SIGTSTP"},
        {SIGTTIN, "SIGTTIN"},
        {SIGTTOU, "SIGTTOU"},
        {SIGURG, "SIGURG"},
        {SIGXCPU, "SIGXCPU"},
        {SIGXFSZ, "SIGXFSZ"},
        {SIGVTALRM, "SIGVTALRM"},
        {SIGPROF, "SIGPROF"},
        {SIGWINCH, "SIGWINCH"},
        {SIGIO, "SIGIO"},
        {SIGPWR, "SIGPWR"},
        {SIGSYS, "SIGSYS"}
    };

    struct sigaction action = {0};

    action.sa_sigaction = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;

    size_t count = sizeof(signals) / sizeof(signals[0]);

    for (size_t i = 0; i < count; i++)
    {
        int sig = signals[i].sig;

        if (sig == SIGKILL || sig == SIGSTOP)
        {
            printf("%s cannot be caught\n", signals[i].name);
            continue;
        }

        if (sigaction(sig, &action, NULL) == -1)
        {
            printf("Cannot register %s: %s\n",
                   signals[i].name, strerror(errno));
        }
        else
        {
            printf("Registered: %s\n", signals[i].name);
        }
    }

    /* Register all real-time signals supported by this system. */
    for (int sig = SIGRTMIN; sig <= SIGRTMAX; sig++)
    {
        if (sigaction(sig, &action, NULL) == -1)
        {
            printf("Cannot register real-time signal %d\n", sig);
        }
        else
        {
            printf("Registered real-time signal: %d\n", sig);
        }
    }

    printf("\nProcess ID: %ld\n", (long)getpid());
    printf("Send signals from another terminal.\n");

    while (1)
    {
        pause();

        if (received_signal != 0)
        {
            int sig = received_signal;
            received_signal = 0;

            printf("Caught signal: %d\n", sig);
            fflush(stdout);
        }
    }

    return 0;
}
