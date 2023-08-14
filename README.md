# TinyCAN-IDS

Disclaimer: THE SAMPLE CODE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL KALANA SAHABANDU OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) SUSTAINED BY YOU OR A THIRD PARTY, HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT ARISING IN ANY WAY OUT OF THE USE OF THIS SAMPLE CODE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

## Summary
The controller area network (CAN) protocol is the most widely used standard in the automotive industry for In-Vehicle Networks (IVN). 
However, this protocol lacks essential security features such as encryption and message authentication, which makes the vehicle network vulnerable to exploits by an adversary. 
Although multiple types of intrusion detection systems have been developed for CAN, they either rely on fixed rule-bases or heuristics provided by a human and have been shown to become ineffective when an unfamiliar or unknown attack is carried out. 
In this paper, we adopt a data-driven approach based on machine learning. 

We develop TinyCAN-IDS, a framework that reasons about the information contained in messages transmitted on the CAN bus to detect four types of attacks - `Flooding, Fuzzing, Spoofing, and Malfunction`. 
TinyCAN-IDS uses `Term Frequency-Inverse Document Frequency` (TF-IDF), a Natural Language Processing (NLP) technique to discern complex features associated with CAN data and Deep Neural Networks (DNN) to effectively determine using these features whether a given message is `Normal` or falls into one of four different attack categories. 
Through extensive experiments on three public vehicle network datasets, we show that the DNN-based TinyCAN-IDS framework yields higher classification accuracies than five widely-used machine learning models.
We also present a lightweight and cost-effective `hardware implementation` of TinyCAN-IDS.
Our implementation uses `Quantization`, a TinyML technique, to reduce the size of the DNN model for effective deployment on resource-constrained hardware.
We demonstrate that the accuracy of TinyCAN-IDS is maintained after model compression.

## Datasets Used
1. CAR HACKING: ATTACK & DEFENSE CHALLENGE 2020 [Link](https://ocslab.hksecurity.net/Datasets/carchallenge2020)
2. CAR-HACKING DATASET [Link](https://ocslab.hksecurity.net/Datasets/car-hacking-dataset)
3. IN-VEHICLE NETWORK INTRUSION DETECTION CHALLENGE [Link](https://ocslab.hksecurity.net/Datasets/datachallenge2019/car)
4. ROAD CAN INTRUSION DATASET [Link](https://0xsam.com/road/)

## Dataset Cleaning
Each dataset is cleaned to a standard dataset format using the following steps:
- Download the dataset using the links above into the `dataset_cleaning` folder.
- Run the `.py` file corresponding to the dataset to get the dataset to a standardized format.
- The standarized format here is defined as single csv file with following columns in the order - `CAN ID, CAN Data, Label`.
- The `CAN ID` is a single column with the value of Arbitration ID.
- The `CAN Data` is a single column where each byte is separated by single whitespace.
- The `Label` values are renamed to 'Normal' or the name of the attack the frame indicates.
## Running main.ipynb
Guide:
- Set the inputs in cell number 2.
- For TSNE plot custom inputs can be set in the end (optional)
- Run the notebook and results are saved in the `results` folder.
