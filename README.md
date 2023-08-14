# TinyCAN-IDS

The `main.py` has the complete implementation of TinyCAN-IDS.

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
