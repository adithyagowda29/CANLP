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
#define MODEL_PATH "./models/dynamic_quant_model.tflite" //fp_16_model.tflite" 
// weigths
const float idf[] = {1.1340105863313785,1.4440750382292602,1.5673999506185683,1.5986519811053719,1.5102271723936755,1.6506853065061653,1.7081950536596389,1.5981019215017138,1.45399508512461,1.7650711754173187,1.745879573399594,1.7481810258770474,1.5720486733050048,1.7422736727907848,1.7223778283266524,1.6496671373670349,1.5110363883381628,2.8756487415438015,3.2642768382035294,3.0747794433395033,3.0022517982720096,2.860753649674639,3.2329388282663145,3.0149534167249934,2.9375521311315707,3.411149540131201,3.359983922160713,3.3493660617902,2.9668540016201517,3.288103423787164,3.3248959485713074,3.094303399414124,2.872783067940915,3.6471162508762367,3.6472455751570507,3.98786504426471,3.916475048178037,4.112398082745939,4.208511715380332,4.138899372841397,3.901854167608664,4.237025948887295,4.111163260609203,4.131105757826585,4.07619961033261,4.197240180357007,4.210327009729518,4.187647245665746,3.158598912608107,3.7927469259492286,4.205116894874277,4.239361307258363,4.02717303395375,4.305069555982813,4.355771659102775,4.257766734801079,4.065335305940704,4.365272918226916,4.283334938992869,4.398982460246664,4.186094278076876,4.3883426108618355,4.325246785268764,4.3539346293249075,3.1165716783212907,4.044724037694782,4.275304721854075,4.339617060784759,4.1365760007961505,4.356559991819991,4.328053267529251,4.234463338282817,4.067695653220649,4.345579489336547,4.343501566510961,4.337035748045305,3.910735667129531,4.359455873796374,4.348182979481944,3.8679025671353946,3.3088167880842665,3.7128538180964514,3.763413258153842,4.22312718449648,3.7993505819445588,4.315864188226776,4.286026072115482,3.724801723494721,3.3657257509861247,4.36262461159434,4.350270662912427,4.386444819862529,4.215107895329861,4.348443701683916,4.3875288308087885,4.34065145446375,3.158281603387612,4.197688610857796,4.310075824260957,4.256338843078224,4.192097631293222,4.459469954877419,4.393511987085622,4.298350605734068,4.130686206740087,4.426510960711651,4.420888230126381,4.430465768126127,4.283823697555874,4.429899837154599,4.447306468684222,4.350009464007978,3.4121714081947796,4.124205573627027,4.22151817369078,4.247578280360644,4.0999145480733326,4.469131865789157,4.473554694759159,4.3778147770883145,4.148460690767664,4.455689232037513,4.449323469800249,4.451344547433502,4.29266244893576,4.462095776955087,4.420607921785372,4.361831485313504,3.430121137075534,4.1021541906668375,4.227738675260388,4.23074758853617,4.190760434748972,4.444145092290649,4.3695248512870375,4.0621968176838426,4.0334331321742205,4.375668853518038,4.358928725655542,4.332919457180424,4.110751991839269,4.148887767434417,3.9780947476185275,3.5284858366566567,2.5089086346463754,3.3526359242920267,3.796343513072093,3.9958972159619743,3.8758359042997923,4.306568806638454,4.317885411754711,3.940114381228383,3.478640701865693,4.3697911983388185,4.395149989089861,4.402279166529156,4.134258014298351,4.390244010321005,4.429051540765542,4.395969997335891,3.4524355036377066,4.21556441211478,4.378351978283076,4.3883426108618355,4.260867512479328,4.507823151593973,4.403105044070936,4.425383882542184,4.184765079830668,4.515189667410736,4.465607633066627,4.458596210828823,4.325246785268764,4.513958140161489,4.438422616016582,4.490842755732399,3.3753364947661,4.145050627787122,4.408351500948396,4.367130914780002,4.163084607297337,4.478888040734521,4.445006295157138,4.4251023113732115,4.160272274454002,4.464142860576812,4.498387683632079,4.508434959505379,4.309574068103917,4.519821449660774,4.478590996324198,4.492949603765298,3.43439799124503,4.230979418837429,4.384280316852957,4.404758848196497,4.219224068532311,4.476217812178643,4.428768935139809,4.423414547259492,4.197464370471163,4.436142763219445,4.493853899230087,4.526030721395758,4.340910220152864,4.426510960711651,4.4467309290999895,4.41001401172201,3.106128114352769,3.9151216390727854,4.213967514319059,4.24404844965712,3.9990179160623116,4.345059603699675,4.370857296520816,4.109724559302571,3.559157006517061,4.348965350104717,4.39706438868999,4.37888946821808,4.240062979606179,4.43131526555793,4.365007771731925,4.390244010321005,3.4128873376551723,4.198810567667959,4.343242129487843,4.387800017251128,4.201283312549364,4.469131865789157,4.419767467890824,4.420607921785372,4.163517976751573,4.477700392138865,4.490241613544173,4.486941775541618,4.296120950406799,4.526965446498867,4.464435643480382,4.467074554262639,3.353310460573927,4.180788052936036,4.318897557590105,4.389700384322296,4.116938854221845,4.468249642529465,4.455398998397397,4.440421759906725,4.127754267467003,4.488740337177532,4.502029569296216,4.458305132381126,4.306068806628037,4.500814133108908,4.524163888246246,4.486043706329934,3.2766100764735326,4.168733112430681,4.205116894874277,3.865325661215935,4.134468518456585,4.350270662912427,4.320164182205298,4.293896255384688,4.058677752468648,4.357348946496023,4.323464934218215,4.368726235511861,4.132785724622369,4.363418367423817,4.372725707580843,3.8215804863805722};

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
  "Spoofing",
  "Normal",
  "Fuzzing"
};

#define NUM_LABELS (sizeof(LABELS) / sizeof(LABELS[0]))

// define how many packets to read (or you can stop with ctrl-c + 1 packet)
#define MAX_PACKETS_TO_READ 27005


void euclideanNormalize(float* arr, size_t size) {
    float sum = 0.0f;
    
    // Calculate the sum of squares of array elements
    for (size_t i = 0; i < size; i++) {
        sum += arr[i] * arr[i];
    }
    
    // Calculate the square root of the sum of squares
    float norm = sqrt(sum);
    
    // Normalize each element
    for (size_t i = 0; i < size; i++) {
        arr[i] /= norm;
    }
}

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
            input_data[i*2] = (int) (frame.data[i] >> 4);
            input_data[i*2+1] = (int) (frame.data[i] & 0x0F);
        }

        // computing the frequencies 
        unsigned short frequencies[272] = {0};

        // then all the frequencies
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

        // euclidean normalize input values
        euclideanNormalize(&inputTensorData[0], 16);
        euclideanNormalize(&inputTensorData[16], 256);
        
        // the last element is the scaled ID
        inputTensorData[272] = (float) frame.can_id / 2048.;

        #ifdef debug
            printf("ID %f\n", inputTensorData[272]);
        #endif

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
            for (short i = 0; i < 3; i++) {
                printf("[%d]: %f \n", i, outputData[i]);
            }
        #endif

        // extracting the predicted label ID
        float max = outputData[0];
        short tmp = 0;
        for (short i = 1; i < 3; i++) {
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

