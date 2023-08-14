import csv

# Combine 8 columns containing CAN data frame into single column and add corresponding label
def process_input_file(input_file_path, attack_type):
    with open(input_file_path, 'r') as input_file:
        reader = csv.reader(input_file)
        for row in reader:
            length_byte = int(row[2])
            combined_column = ' '.join(row[3:3+length_byte]).upper()
            row[3+length_byte] = "Normal" if row[3+length_byte] == "R" else attack_type
            writer.writerow([row[1], combined_column, row[3+length_byte]])

# Dictionary of all indivudal attack dataset files
datasets = {
    'Car_Hacking_Dataset/DoS_dataset.csv': 'DoS',
    'Car_Hacking_Dataset/Fuzzy_dataset.csv': 'Fuzzy',
    'Car_Hacking_Dataset/gear_dataset_2_new.csv': 'Spoofing',
    'Car_Hacking_Dataset/RPM_dataset_new.csv': 'Spoofing'
}

with open('Car_Hacking_Dataset_All_multiclass.csv', 'w', newline='') as output_file:
    writer = csv.writer(output_file)
    
    for dataset_path, attack_type in datasets.items():
        process_input_file(dataset_path, attack_type)
