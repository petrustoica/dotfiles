#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// status code 1 means too few arguments
// status code 2 means failed to parse number

//volume --set 1 --increment 3

//dunstify "Volume: 1.0" -t 1250 -r 19060


int sgn(float val){
   if(val > 0)
       return 1;
   else if(val < 0)
       return -1;
   else
       return 0;
}

int main( int argc, char *argv[] ){
    char wpctlBuffer[100];
    for( int i = 1; i < argc; i += 1 ){
        if( !strcmp(argv[i], "-s") || !strcmp(argv[i], "--set") || !strcmp(argv[i], "set") ) {
            if( i + 1 >= argc ) return 1;
            char *end;
            float value = strtof(argv[i + 1], &end);
            if( *end != '\0' ) return 2;
            if( value > 5.0 ) value = 5.0;
            if( value < 0.0 ) value = 0.0;
            sprintf(wpctlBuffer, "wpctl set-volume @DEFAULT_AUDIO_SINK@ %.3f", value);
            system(wpctlBuffer);
            system("dunstify \"$(wpctl get-volume @DEFAULT_AUDIO_SINK@)\" -t 1250 -r 19060");
            i += 1;
        }else if( !strcmp(argv[i], "-a") || !strcmp(argv[i], "--add") || !strcmp(argv[i], "add") ){
            if( i + 1 >= argc ) return 1;
            char *end;
            float value = strtof(argv[i + 1], &end);
            if( *end != '\0' ) return 2;
            sprintf(wpctlBuffer, "wpctl set-volume @DEFAULT_AUDIO_SINK@ %.3f%c", value * sgn(value), ( (sgn(value) == 1) ? '+' : '-') );
            printf(wpctlBuffer);
            system(wpctlBuffer);
            system("dunstify \"$(wpctl get-volume @DEFAULT_AUDIO_SINK@)\" -t 1250 -r 19060");
        }else if( !strcmp(argv[i], "-mute") ){ 
            if( i + 1 >= argc ) return 1;
            switch(argv[i + 1][0]){
                case('1'):
                    system("wpctl set-mute @DEFAULT_AUDIO_SINK@ 1");
                    break;
                case('0'):
                    system("wpctl set-mute @DEFAULT_AUDIO_SINK@ 0");
                    break;
                case('t'):
                    system("wpctl set-mute @DEFAULT_AUDIO_SINK@ toggle");
                    break;
            }
            system("dunstify \"$(wpctl get-volume @DEFAULT_AUDIO_SINK@)\" -t 1250 -r 19060");
        }else if( !strcmp(argv[i], "-mute-mic") ){ 
            if( i + 1 >= argc ) return 1;
            switch(argv[i + 1][0]){
                case('1'):
                    system("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ 1");
                    break;
                case('0'):
                    system("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ 0");
                    break;
                case('t'):
                    system("wpctl set-mute @DEFAULT_AUDIO_SOURCE@ toggle");
                    break;
            }
            system("dunstify \"Microphone $(wpctl get-volume @DEFAULT_AUDIO_SOURCE@)\" -t 1250 -r 19060");
        }
    }
    return 0;
}
