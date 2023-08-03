/*
 * TinyCAN-IDS on Raspberry Pi 4
 */

// tensorflow
#include <tensorflow/lite/c/common.h>
#include <tensorflow/lite/c/c_api.h>

// stdlib
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <math.h>
#include <time.h>

// Libraries for connecting to CAN socket
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <net/if.h>

// Libraries for linux-can-utils
#include <linux/can.h>
#include <linux/can/raw.h>

#define MAX_DATA_SIZE 8 //bytes
#define TF_LITE_STATIC_MEMORY 1
#define MODEL_PATH "./models/dynamic_quant_model.tflite"
// weigths
const signed short idf[] = {1.0908490265743185,1.5734057533774553,1.639890134454822,2.3211920740107974,2.2594314111747105,2.023819784888471,2.437956606778253,2.323913164125158,1.610832764569731,2.534794930185841,2.4557591995088526,2.5262335527482467,2.35747026074099,2.480589990902815,1.9902995573092421,1.925435780029594,1.3071786159269339,2.091068111635151,2.760277663853223,3.9541532950150473,3.864055495822228,4.021271131485106,4.199962920228482,3.776220540928526,2.5992586877631365,4.504921169872132,4.1555111576576484,4.4810789809093725,4.065197111942952,4.367376393934151,4.315032250013269,3.8144585546828558,2.6263365191229875,4.367376393934151,4.442563308828758,4.606416659163586,4.749745787247666,4.58585793214255,4.8813221450363855,4.885236044357521,4.846769763529726,4.8813221450363855,4.82069752321995,4.8813221450363855,4.828077630517573,4.753176322344455,4.6707573759290355,4.806098723798797,2.6941303672315597,4.603453694032929,4.82069752321995,4.8696715278164096,4.65194804397154,2.936528690681147,4.861979182193254,5.019327818055829,2.9320693744843824,5.103489610377539,5.046602235975488,4.90904669305124,4.8735400045943305,5.010399187311528,5.060523574494097,2.9387658280795037,3.866884352022706,4.543177201027669,4.798878475825311,5.014853537660908,4.8696715278164096,5.010399187311528,5.060523574494097,4.568566435032489,4.941702656025293,4.984081878994154,5.206143764437623,5.217013436674526,4.624381214138885,5.163809400611062,5.184752574456305,4.78105269187271,4.288772535429714,4.3910181569911915,4.591688852453343,4.950036037584438,4.749745787247666,4.749745787247666,4.984081878994154,4.7193893247670715,4.504921169872132,4.817027794330988,4.979762217849638,4.913070843350965,4.8696715278164096,4.905038671653701,5.1281822229679115,4.706187812908536,2.799442172497014,5.010399187311528,4.861979182193254,5.019327818055829,4.763539109380002,5.037427859699447,5.001549572034545,4.975461135950248,5.065207423806522,5.084165337551137,5.079392058798479,5.0699133148439355,5.065207423806522,5.153500030952201,5.0699133148439355,5.0238222076436685,4.2219418269472575,4.854345557338183,4.905038671653701,4.929331364222746,4.937561863359262,5.138232558821413,5.055861561388285,5.042004526726859,5.028336887998195,5.0699133148439355,4.8735400045943305,5.15864143045262,4.992777585961708,5.108379595671732,5.055861561388285,4.966914075371789,4.393413367717146,4.90904669305124,4.680296398975795,4.835512609005091,5.060523574494097,5.042004526726859,4.941702656025293,4.82069752321995,4.7600729014035155,5.0512211818317825,5.010399187311528,4.824380768636247,5.037427859699447,4.817027794330988,4.65194804397154,4.170749547762581,2.568245407329919,4.468074896486166,2.9326257027323885,4.889165322497411,4.749745787247666,4.92524137897122,5.046602235975488,4.7600729014035155,4.450148680218014,5.065207423806522,5.211563831906962,5.0699133148439355,4.5771748095690885,5.084165337551137,2.9534305014837505,4.798878475825311,4.455237749725486,4.984081878994154,5.093780796250579,5.093780796250579,4.941702656025293,5.206143764437623,5.055861561388285,5.001549572034545,5.079392058798479,5.1331947647914555,5.190057626685999,5.028336887998195,5.169004217488166,5.019327818055829,5.169004217488166,5.037427859699447,4.2444146827993166,4.597553971905741,5.032872043163587,4.954228915844473,5.019327818055829,5.118231892114743,5.065207423806522,5.1331947647914555,5.143295860777959,5.174226161469318,5.179475517355462,5.079392058798479,5.0986234207263665,5.123194681456872,5.079392058798479,5.08896150981463,4.510297526908513,4.966914075371789,5.163809400611062,5.065207423806522,4.966914075371789,5.084165337551137,4.992777585961708,5.0699133148439355,5.032872043163587,5.190057626685999,5.118231892114743,5.233542738625737,5.1331947647914555,5.0699133148439355,5.019327818055829,4.889165322497411,4.053179799938935,4.802482083328609,4.979762217849638,4.6426744071862105,4.648847266293291,5.037427859699447,5.1281822229679115,4.921168053583585,4.568566435032489,5.032872043163587,5.084165337551137,5.113293610474161,5.113293610474161,5.0699133148439355,5.163809400611062,5.108379595671732,4.284462183928591,4.877423504620728,5.0238222076436685,5.014853537660908,4.913070843350965,5.138232558821413,4.984081878994154,4.984081878994154,4.8735400045943305,5.108379595671732,5.195390972661361,5.195390972661361,5.138232558821413,5.163809400611062,5.143295860777959,5.010399187311528,4.146103750555753,4.791709986346698,2.9483298953561627,4.767017373756326,4.667597815638667,5.113293610474161,4.971178474158247,5.005964590243662,4.7193893247670715,5.1281822229679115,5.250349856942119,5.256015594477796,5.046602235975488,5.037427859699447,5.15864143045262,5.138232558821413,3.85421704682194,4.962667784490337,2.917164323499356,4.78105269187271,4.988420280592752,5.074641456039881,4.756618666535428,4.897070502004524,4.901046650384163,5.065207423806522,4.763539109380002,5.042004526726859,4.365042670587931,5.014853537660908,4.358074001271838,2.727110183259211};

// debug: define to print packets and other info (may slow down the system)
//#define debug 1

unsigned short input_data[MAX_DATA_SIZE*2] = {0};

// catch ctrl+c
static volatile short keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}

// array to map gesture index to a name
const char* LABELS[] = {
  "Normal",
  "Flooding",
  "Spoofing",
  "Fuzzing"
};

#define NUM_LABELS (sizeof(LABELS) / sizeof(LABELS[0]))

// define how many packets to read (or you can stop with ctrl-c + 1 packet)
#define MAX_PACKETS_TO_READ 10000

int main() {

    // *********** SETUP TENSORFLOW **************
    // Load the TensorFlow Lite model
    TfLiteModel* model = TfLiteModelCreateFromFile(MODEL_PATH);
    if (model == NULL) {
        printf("Error loading the model: %s\n", MODEL_PATH);
        return 1;
    }

    // Create interpreter options (optional)
    TfLiteInterpreterOptions* options = TfLiteInterpreterOptionsCreate();
    // Set any interpreter options here (e.g., number of threads, delegate, etc.)

    // Create the interpreter
    TfLiteInterpreter* interpreter = TfLiteInterpreterCreate(model, options);
    if (interpreter == NULL) {
        printf("Error creating the interpreter.\n");
        return 1;
    }

    // Allocate tensor buffers
    if (TfLiteInterpreterAllocateTensors(interpreter) != kTfLiteOk) {
        printf("Error allocating tensors.\n");
        return 1;
    }

    // Get the input tensor
    TfLiteTensor* inputTensor = TfLiteInterpreterGetInputTensor(interpreter, 0);


    //************** SETUP CAN *******************
    struct sockaddr_can addr;
    struct ifreq ifr;

    int s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s < 0) {
        printf("socket error\n");
        return 1;
    }
    addr.can_family = AF_CAN;

    memset(&ifr.ifr_name, 0, sizeof(ifr.ifr_name));
    strcpy(ifr.ifr_name, "can1");

    if (strcmp("any", ifr.ifr_name)) {
        if (ioctl(s, SIOCGIFINDEX, &ifr) < 0) {
            printf("SIOCGIFINDEX\n");
            return 1;
        }
        addr.can_ifindex = ifr.ifr_ifindex;
    } else
        addr.can_ifindex = 0;

    int ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));
    struct can_frame frame;

    bool quit_var = false;
    int nbytes = 0;

    // set hadler to stop and print stuff on ctrl+c
    signal(SIGINT, intHandler);


    // ************ STARTING THE IDS ***************************
    printf("Setup done. Start reading packets...\n");
    unsigned int processed_pcks = 0;
    short labels[MAX_PACKETS_TO_READ];
    double times[MAX_PACKETS_TO_READ];

    while (keepRunning) {

        nbytes = read(s, &frame, sizeof(struct can_frame));

        clock_t start, end;
        double cpu_time_used;
        start = clock();

        // printing packets
        #ifdef debug
            printf("%03x %02d ", frame.can_id, frame.can_dlc);
            char msg[17];
            for(int i=0; i<frame.can_dlc; i++) {
                sprintf(msg+i*2, "%02x", frame.data[i]);
            }
            printf(msg);
            printf("\n");
            fflush(stdout);
        #endif

        // // convert to "4-bit" chars        
        unsigned short input_data[16] = {0};
        for (unsigned short i=0; i<frame.can_dlc; i++) {
            input_data[i*2] = frame.data[i] >> 4;
            input_data[i*2+1] = frame.data[i] & 0x0F;
        }

        // computing the frequencies 
        unsigned short frequencies[272] = {0};
        for (unsigned short i = 0; i < 16; i++) {
            frequencies[input_data[i]]++;
            if(i<15){
                frequencies[16*input_data[i]+input_data[i+1]+16]++; 
            }
        }

        // Fill the input tensor with your data
        float* inputTensorData = (float*)TfLiteTensorData(inputTensor);
        for (unsigned short i = 0; i < 272; i++) {
            inputTensorData[i] = frequencies[i] * idf[i];
        }

        // Run inference
        if (TfLiteInterpreterInvoke(interpreter) != kTfLiteOk) {
            printf("Error running the inference.\n");
            return 1;
        }

        // Get the output tensor
        TfLiteTensor* outputTensor = TfLiteInterpreterGetOutputTensor(interpreter, 0);

        end = clock();
        cpu_time_used = ((double) (end - start) / CLOCKS_PER_SEC * 1000);
        #ifdef debug
            printf("Time: %fms\n", cpu_time_used);
        #endif

        // Get a pointer to the output tensor data
        float* outputData = (float*)TfLiteTensorData(outputTensor);

        // Process the output data
        #ifdef debug
            for (short i = 0; i < 4; i++) {
                printf("[%d]: %f ", i, outputData[i]);
            }
        #endif

        // extracting the predicted label ID
        short max = outputData[0];
        short tmp = 0;
        for (short i = 1; i < 4; i++) {
            if (outputData[i] > max) {
                max = outputData[i];
                tmp = i;
            }
        }

        // saving times
        times[processed_pcks] = cpu_time_used;
        labels[processed_pcks++] = tmp;

        // check if reached MAX_PACKETS_TO_READ
        if(processed_pcks >= MAX_PACKETS_TO_READ) { 
            keepRunning = 0; 
        } 
	}

    // **************** COMPUTING SCORES ***************************
    // the first packet has usually an abnormal time
    // we can consider the "runtime" delay skipping the first packets
    short PACKETS_TO_SKIP = 5;
    processed_pcks -= PACKETS_TO_SKIP;

    // compute mean and stdev
    double total_time = 0;
    for(short i = PACKETS_TO_SKIP; i < processed_pcks; i++) {
        total_time += times[i];
    }
    double mean = total_time/processed_pcks;

    double stdev = 0;
    for(short i = PACKETS_TO_SKIP; i < processed_pcks; i++) {
        stdev += pow(times[i] - mean, 2);
    }

    stdev = sqrt(stdev / processed_pcks);

    char info[100];
    sprintf(info, "\nPckt: %d - Mean: %f - Stdev: %f\n", processed_pcks, mean, stdev);

    // dump results in a file
    char filename[100];
    sprintf(filename, "output_data_%u.log", (unsigned)time(NULL));

    FILE *f = fopen(filename, "w");
    fputs(info, f);
    fputs("label,delay\n", f);
    for(int i=PACKETS_TO_SKIP; i<processed_pcks; i++)
    {
        fprintf(f,"%d,%f\n",labels[i],times[i]);
    }

    fclose(f);

    return 0;
}
