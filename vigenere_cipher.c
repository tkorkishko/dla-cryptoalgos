#include <stdio.h>
#include <strings.h>
#include <memory.h> 

#define TEST_NUM 3

#define MAX_KEY_LEN 25
#define MAX_PT_LEN 128
#define ALPHABET_SIZE 26
#define ASCII_LOW_CASE_SHIFT 97

struct vc_test {
    char* key;
    char* pt;
    char* ct;
};

typedef struct vc_test vc_test;

vc_test vc_test_set[TEST_NUM];

void init_vc_test_set() {
    vc_test_set[0].key = "secretkey";
    vc_test_set[0].pt = "sampleplaintext";
    vc_test_set[0].ct = "keogpxzpyarvvbm";
    
    vc_test_set[1].key = "testkey";
    vc_test_set[1].pt = "thisisnicetestinputforvtest";
    vc_test_set[1].ct = "mlalswlbgwmowrbrhndjmkzlxcx";
    
    vc_test_set[2].key = "ab";
    vc_test_set[2].pt = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    vc_test_set[2].ct = "abababababababababababababababababababab";
}

void v_encrypt(char *key, char *pt, char *ct) {
    int index;
    int key_len = strlen(key);
    
    for(index = 0; index < strlen(pt); index++) 
        ct[index] = ((pt[index] - ASCII_LOW_CASE_SHIFT) + 
            (key[index % key_len] - ASCII_LOW_CASE_SHIFT)) % ALPHABET_SIZE 
            + ASCII_LOW_CASE_SHIFT;
}

void v_decrypt(char *key, char *ct, char *pt) {
    int index;
    int key_len = strlen(key);
    int a;
    
    for(index = 0; index < strlen(ct); index++) {
        a = (ct[index] - ASCII_LOW_CASE_SHIFT) - (key[index % key_len] - ASCII_LOW_CASE_SHIFT);
        //handle potential negative num
        if( a < 0) 
            a = ALPHABET_SIZE + a;

        pt[index] = a + ASCII_LOW_CASE_SHIFT;
    }
}

int v_test_runner() {
    char candidate[MAX_PT_LEN];
    int test_index;
    
    init_vc_test_set();
    
    for(test_index = 0; test_index < TEST_NUM; test_index++) {
        memset(candidate, 0, MAX_PT_LEN);
        //encryption test
        v_encrypt(vc_test_set[test_index].key, vc_test_set[test_index].pt, candidate);
        if(strcmp(candidate, vc_test_set[test_index].ct) != 0) {
            printf("Test %d Encryption FAILED\n", test_index);
            return 1;
        }
        
        //decryption text
        memset(candidate, 0, MAX_PT_LEN);
        v_decrypt(vc_test_set[test_index].key, vc_test_set[test_index].ct, candidate);
        if(strcmp(candidate, vc_test_set[test_index].pt) != 0) {
            printf("Test %d Decryption FAILED\n", test_index);
            return 1;
        }
        
    }
    //self test passed
    return 0;
}

int main() {

    char pt[MAX_PT_LEN] = {0};
    char key[MAX_KEY_LEN] = {0};
    char ct[MAX_PT_LEN] = {0};
    int test_res;
    
    //Run known test vectors self-test
    test_res = v_test_runner();
    if(test_res != 0) {
        printf("Self test FAILED. Exiting.");
        return 1;
    }
    
    //Process user input
    printf("Unsafe reading of input (string overflow is possibe), lower case alpha characters only, no whitespaces\n");
    printf("Length limits, characters: key - %d plaintext - %d\n", MAX_KEY_LEN, MAX_PT_LEN);
    printf("Enter key:           ");
    scanf("%s", key);
    printf("\nEnter plaintext:     ");
    scanf("%s", pt);
    v_encrypt(key, pt, ct);
    printf("\nCiphertext:          %s", ct);
    v_decrypt(key, ct, pt);
    printf("\nDecrypted plaintext: %s\n", pt);
    
    return 0;
}
