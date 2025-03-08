#include "logLib.h"

#define SIG_GEN_DUMP SIGRTMIN
#define SIG_TOGGLE_LOGGING (SIGRTMIN+1)
#define SIG_CHANGE_LOG_LEVEL (SIGRTMIN+2)


static u_int8_t loggin_enabled = 1;
static log_level_t current_log_level = STANDARD;
static int init_status = 0;

pthread_t gen_dump_tid, toggle_logging_tid,change_log_level_tid;

static sem_t gen_dump_SignalHandler;
static sem_t toggle_logging_SignalHandler;
static sem_t change_log_SignalHandler;

static pthread_mutex_t log_level_MUTEX;
static pthread_mutex_t log_write_MUTEX;

FILE *dumpP;
FILE *logP;

char *logFileName = "logger.txt";

void* gen_dump();
void* toggle_logging();
void* change_log_level();

void handler_gen_dump();
void handle_toggle_logging();
void handle_change_log_level();

void init_logger(){
    
    printf("%d\n",getppid());

    if(init_status == 1){
        return;
    }

    if(pthread_mutex_init(&log_level_MUTEX, NULL)){
        printf("1. Mutex init failed\n Exiting...\n");
        return;
    }

    if(pthread_mutex_init(&log_write_MUTEX, NULL)){
        printf("2. Mutex init failed\n Exiting...\n");
        return;
    }

    

    struct sigaction signal1;
    sigset_t set;

    sigfillset(&set);

    signal1.sa_sigaction = handler_gen_dump;
    signal1.sa_mask = set;
    signal1.sa_flags = SA_SIGINFO;
    sigaction(SIG_GEN_DUMP, &signal1, NULL);

    signal1.sa_sigaction = handle_toggle_logging;
    signal1.sa_mask = set;
    signal1.sa_flags = SA_SIGINFO;
    sigaction(SIG_TOGGLE_LOGGING , &signal1, NULL);

    signal1.sa_sigaction = handle_change_log_level;
    signal1.sa_mask = set;
    signal1.sa_flags = SA_SIGINFO;
    sigaction(SIG_CHANGE_LOG_LEVEL, &signal1, NULL);
    
    pthread_create(&gen_dump_tid, NULL, gen_dump, NULL);
    pthread_create(&toggle_logging_tid, NULL, toggle_logging, NULL);
    pthread_create(&change_log_level_tid, NULL, change_log_level, NULL);
    
    init_status = 1;
    return;
}

void cleanUpProcesses(){
    
    pthread_exit(&gen_dump_tid);
    pthread_exit(&toggle_logging_tid);
    pthread_exit(&change_log_level_tid);
    
    if(!pthread_mutex_destroy(&log_level_MUTEX)){
        printf("Mutex destruction failed\n Exiting...\n ");
        return;
    }
    if(!pthread_mutex_destroy(&log_write_MUTEX)){
        printf("Mutex destruction failed\n Exiting...\n ");
        return;
    }
}


void write_log(const char *message, log_level_t level){
    if(pthread_mutex_trylock(&log_level_MUTEX) != EBUSY && pthread_mutex_trylock(&log_write_MUTEX) != EBUSY){
        pthread_mutex_lock(&log_level_MUTEX);
        pthread_mutex_lock(&log_write_MUTEX);
        
        if(loggin_enabled != 1 || level > current_log_level){
            if((logP = fopen(logFileName, "a"))){
                fprintf(logP, "%s - level: %d\n", message,level);
                fclose(logP);
            }
        }else{
            printf("Unable to write to LogFile\n");
        }
        pthread_mutex_unlock(&log_level_MUTEX);
        pthread_mutex_unlock(&log_write_MUTEX);
    }  
    fclose(logP);
}

//funkcja na gen_dump
void* gen_dump(){
    
    while (1)
    {
        sem_wait(&gen_dump_SignalHandler);
        
        char filname[256];
        time_t now = time(NULL);
        snprintf(filname, sizeof(filname), "%s%ld.txt", "dump_",now);
        if((dumpP = fopen(filname,"w"))){
            fprintf(dumpP, "WYGENEROWANO PLIK DUMP W MOMENCIE: %ld\n",now);
            fprintf(dumpP,"current_log_level: %d, loggin_enabled: %d\n",current_log_level,loggin_enabled);
            fclose(dumpP);
        }
    }
    
}
void handler_gen_dump(void *arg){
    sem_post(&gen_dump_SignalHandler);
}

//funkcja na toggle_logging
void* toggle_logging(){
    while (1)
    {
        sem_wait(&toggle_logging_SignalHandler);

        pthread_mutex_lock(&log_write_MUTEX);
        loggin_enabled = (loggin_enabled + 1) % 2;
        pthread_mutex_unlock(&log_write_MUTEX);

    }
}
void handle_toggle_logging(){
    sem_post(&toggle_logging_SignalHandler);
}

//funkcja na change_log
void* change_log_level(){
    while (1)
    {
        sem_wait(&change_log_SignalHandler);

        pthread_mutex_lock(&log_level_MUTEX);
        current_log_level = (current_log_level + 1) % 3;
        pthread_mutex_unlock(&log_level_MUTEX);
    }
    exit(0);
}
void handle_change_log_level(){
    sem_post(&change_log_SignalHandler);
}