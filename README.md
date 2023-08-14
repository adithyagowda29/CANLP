# TinyCAN-IDS

## Summary
The controller area network (CAN) protocol is the most widely used standard in the automotive industry for In-Vehicle Networks (IVN). 
However, this protocol lacks essential security features such as encryption and message authentication, which makes the vehicle network vulnerable to exploits by an adversary. 
Although multiple types of intrusion detection systems have been developed for CAN, they either rely on fixed rule-bases or heuristics provided by a human and have been shown to become ineffective when an unfamiliar or unknown attack is carried out. 
In this paper, we adopt a data-driven approach based on machine learning. 
We develop TinyCAN-IDS, a framework that reasons about the information contained in messages transmitted on the CAN bus to detect four types of attacks - `Flooding, Fuzzing, Spoofing, and Malfunction`. 
TinyCAN-IDS uses `Term Frequency-Inverse Document Frequency` (TF-IDF), a Natural Language Processing (NLP) technique to discern complex features associated with CAN data and Deep Neural Networks (DNN) to effectively determine using these features whether a given message is `normal' or falls into one of four different attack categories. 
Through extensive experiments on three public vehicle network datasets, we show that the DNN-based TinyCAN-IDS framework yields higher classification accuracies than five widely-used machine learning models.
We also present a lightweight and cost-effective `hardware implementation` of TinyCAN-IDS.
Our implementation uses `Quantization`, a TinyML technique, to reduce the size of the DNN model for effective deployment on resource-constrained hardware.
We demonstrate that the accuracy of TinyCAN-IDS is maintained after model compression.

## Datasets Used
1. CAR HACKING: ATTACK & DEFENSE CHALLENGE 2020 [link](https://ocslab.hksecurity.net/Datasets/carchallenge2020)
2. CAR-HACKING DATASET [link](https://ocslab.hksecurity.net/Datasets/car-hacking-dataset)
3. IN-VEHICLE NETWORK INTRUSION DETECTION CHALLENGE [link](https://ocslab.hksecurity.net/Datasets/datachallenge2019/car)
4. ROAD CAN INTRUSION DATASET [link](https://0xsam.com/road/)

## Dataset Cleaning
Each dataset is cleaned to a standard dataset format:
- Timestamp is removed from frames
- CAN Data frame is a single column where each byte is separated by single space
- Labels are renamed to 'Normal' or the name of the attack the frame indicates  
Each sub-dataset containing attacks in combined into a single dataset file for a true multi-class classification model.
## Running main.py
Guide:
- Set the inputs in cell number 2.
- For TSNE plot custom inputs can be set in the end (optional)
- Run the notebook
