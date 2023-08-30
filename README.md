# CANLP - Natural Language Processing-Based Intrusion Detection System for CAN

Disclaimer: THE SAMPLE CODE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL KAYVA BALASUBRAMANIAN AND ADITHYA GOWDA BARAGUR OR OTHER CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) SUSTAINED BY YOU OR A THIRD PARTY, HOWEVER, CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT ARISING IN ANY WAY OUT OF THE USE OF THIS SAMPLE CODE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## Summary
In-vehicle security has been a rising concern especially due to modern vehicles using software-driven Electronic Control Units (ECUs) and wireless connectivity. 
The CAN protocol is the most popular and extensively used in-vehicle messaging standard in the automotive industry. 
However, the design of the CAN protocol does not include essential security features such as encryption or message authentication, which makes the vehicle network vulnerable to exploits by an adversary. 
Previous research has demonstrated how an adversary can exploit vulnerabilities in remote endpoints to compromise an ECU, access the in-vehicle network, and cause abnormal vehicle behavior thus jeopardizing driver and passenger safety.

We develop CANLP, an NLP-based Intrusion Detection System (IDS) to effectively determine whether a transmitted message originated from a legitimate ECU or an adversary and identify the ECU on which the attack was mounted. 
CANLP uses `Term Frequency-Inverse Document Frequency (TF-IDF)`, a Natural Language Processing (NLP) technique to discern complex features associated with CAN data and trains Machine Learning (ML) models with these features to perform attack classification. It detects Time Opaque attacks which consist of - `Fuzzing, Targeted ID, and Masquerade`.
- For a `Fuzzing` attack, messages with random IDs and arbitrary payloads are injected into the bus. 
- In the case of a `Targeted ID` attack, the adversary can inject messages with a specific target ID and manipulated data field which is referred to as targeting a signal. 
- To implement `Masquerade` attacks, the adversary first suspends messages of a specific weakly compromised target ECU, for instance, using bus off attack, and then injects spoofed messages with this target ID using a strongly compromised ECU, thus masquerading as the target ECU.

Through extensive experiments on four public vehicle network datasets, we show that the DNN-based CANLP framework yields higher classification accuracies than five widely used machine learning models.
We also present a lightweight and cost-effective `hardware implementation` of CANLP.
Our implementation uses `Quantization`, a TinyML technique, to reduce the size of the DNN model for effective deployment on resource-constrained hardware.
We also demonstrate that the accuracy of CANLP is maintained after model compression.
We also show that CANLP can be effectively deployed for attack detection on resource-constrained hardware through experiments on a CAN bus testbed.

## Datasets Used
1. CAR HACKING: ATTACK & DEFENSE CHALLENGE 2020 [Link](https://ocslab.hksecurity.net/Datasets/carchallenge2020)
2. CAR-HACKING DATASET [Link](https://ocslab.hksecurity.net/Datasets/car-hacking-dataset)
3. IN-VEHICLE NETWORK INTRUSION DETECTION CHALLENGE [Link](https://ocslab.hksecurity.net/Datasets/datachallenge2019/car)
4. ROAD CAN INTRUSION DATASET [Link](https://0xsam.com/road/)

## Models Used
1. Support Vector Machine (SVM)
2. Logistic Regression (LR)
3. Gaussian Naive Bayes (GNB)
4. Decision Trees (DT)
5. Random Forest (RF)
6. Deep Neural Network (DNN)

## Dataset Cleaning - (Optional)
Each dataset is cleaned to a standard dataset format using the following steps:
- Download the dataset using the links above into the `dataset_cleaning` folder.
- Run the `.py` file corresponding to the dataset to get the dataset to a standardized format.
- The standard format here is defined as a single CSV file with the following columns in the order - `CAN ID, CAN Data, Label`.
- The `CAN ID` is a single column with the value of Arbitration ID.
- The `CAN Data` is a single column where each byte is separated by a single whitespace.
- The `Label` values are renamed to 'Normal' or the name of the attack the frame indicates.
- The generated CSV file in the `dataset_csv` folder containing `no_duplicates` is used for the next steps.

## Procedure to Run
- Clone the repository on the local machine - `git clone https://github.com/adithyagowda29/CANLP`.
- Install all required libraries using - `pip install -r requirements.txt`.
- Select a CSV file in the `dataset_csv` folder.
- Open `main.ipynb` and set all the inputs in cell number 2.
- Run the notebook and results are saved in the `results` folder.

For the procedure on implementing on hardware, go to the `hardware_deployment` folder.
