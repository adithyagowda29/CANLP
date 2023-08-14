import csv

def write_filtered_rows_to_output(input_file_path, writer):
    
    with open(input_file_path, 'r') as input_file:
        reader = csv.reader(input_file)
        next(reader)
        
        #Remove replay attacks from dataset
        for row in reader:
            if row[5] != "Replay":
                writer.writerow([row[1], row[3], row[5]])

output_path = 'Attack_Dataset_Stationary_All_multiclass.csv'
input_files = ['0_Training/Pre_train_S_1.csv', '0_Training/Pre_train_S_2.csv']

with open(output_path, 'w', newline='') as output_file:
    writer = csv.writer(output_file)
    
    # Process each input file and write the filtered rows to the output file
    for input_file in input_files:
        write_filtered_rows_to_output(input_file, writer)
