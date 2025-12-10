#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// status code 1 means too few arguments
// status code 2 means failed to parse number

//brightness --set 1 --increment 3


int main( int argc, char *argv[] ){
    FILE *BRIGHTNESS_FILE_PTR;
    BRIGHTNESS_FILE_PTR = fopen("/sys/class/backlight/intel_backlight/brightness", "r+");
    
    char dunstifyBuffer[100];

    for( int i = 1; i < argc; i += 1 ){
        if( !strcmp(argv[i], "-s") || !strcmp(argv[i], "--set") || !strcmp(argv[i], "set") ) {
            if( i + 1 >= argc ) return 1;
            char *end;
            int value = strtol(argv[i + 1], &end, 10);
            if( *end != '\0' ) return 2;
            if( value > 496 ) value = 496;
            if( value <   0 ) value =   0;
            BRIGHTNESS_FILE_PTR = freopen("/sys/class/backlight/intel_backlight/brightness", "w", BRIGHTNESS_FILE_PTR);
            sprintf(dunstifyBuffer, "dunstify \"Brightness: %.1f\" -t 1250 -r 19066", value / 496.0f);
            system(dunstifyBuffer);
            fprintf(BRIGHTNESS_FILE_PTR, "%d", value);
            i += 1;
        }else if ( !strcmp(argv[i], "-g") || !strcmp(argv[i], "--get") || !strcmp(argv[i], "get") ){
            int oldBrightness;
            fscanf(BRIGHTNESS_FILE_PTR, "%d", &oldBrightness);
            printf("%d", oldBrightness);
        }else if ( !strcmp(argv[i], "-a") || !strcmp(argv[i], "--add") || !strcmp(argv[i], "add") ){
            if( i + 1 >= argc ) return 1;
            char *end;
            int value = strtol(argv[i + 1], &end, 10);
            if( *end != '\0' ) return 2;
            int brightness;
            fscanf(BRIGHTNESS_FILE_PTR, "%d", &brightness);
            BRIGHTNESS_FILE_PTR = freopen("/sys/class/backlight/intel_backlight/brightness", "w", BRIGHTNESS_FILE_PTR);
            brightness += value;
            if( brightness > 496 ) brightness = 496;
            if( brightness < 0 ) brightness = 0;
            sprintf(dunstifyBuffer, "dunstify \"Brightness: %.1f\" -t 1250 -r 19066", brightness / 496.0f);
            system(dunstifyBuffer);
            fprintf(BRIGHTNESS_FILE_PTR, "%d", brightness);
        }
    }
    fclose(BRIGHTNESS_FILE_PTR);
    return 0;
}
