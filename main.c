#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define struct_field(x) ((int) sizeof(x)), x

struct otp {
    char private_id[12];
    char usage_count[4];
    char timestamp[6];
    char session_usage_counter[2];
    char random_number[4];
    char checksum[4];
};

struct yubicode {
    char id[12];
    struct otp otp;
};

char integer_to_hexchar(int value) {
    if(0 <= value && value <= 9) {
        return '0' + value;
    } else if(10 <= value && value <= 15) {
        return 'a' + (value - 10);
    } else {
        return '\0';
    }
}

char* modhex_to_hex(char* src, size_t len, char* dest) {
    const char alphabet[] = "cbdefghijklnrtuv";
    const int alphabet_len = sizeof(alphabet) / sizeof(char);
    
    for(int i = 0; i < len; ++i) {
        for(int j = 0; j < alphabet_len; ++j) {
            if(src[i] == alphabet[j]) {
                // sprintf(&(dest[i]), "%X", j);
                dest[i] = integer_to_hexchar(j);
                break;
            }
        }
    }
    dest[len] = '\0';
    return dest;
}

void print_otp(struct otp* this) {
    printf("OTP(");
    printf("private_id=%.*s, ", struct_field(this->private_id));
    printf("usage_count=%.*s, ", struct_field(this->usage_count));
    printf("timestamp=%.*s, ", struct_field(this->timestamp));
    printf("session_usage_counter=%.*s, ", struct_field(this->session_usage_counter));
    printf("random_number=%.*s, ", struct_field(this->random_number));
    printf("checksum=%.*s", struct_field(this->checksum));
    printf(")");
}

void print_yubicode(struct yubicode* this) {
    printf("Yubicode(");
    printf("id=%.*s,", struct_field(this->id));
    printf("otp=");
    print_otp(&this->otp);
    printf(")");
}

int main() {
    char modhex[45];
    char hex_code[45];

    fread(modhex, sizeof(modhex), sizeof(char), stdin);

    printf("Yubikey code => %s", modhex);

    modhex_to_hex(modhex, sizeof(modhex), hex_code);

    struct yubicode yubicode = *((struct yubicode *) &hex_code);
    print_yubicode(&yubicode);
    printf("\n");

    return 0;
}