/*
Fast Artificial Neural Network Library (fann)
Copyright (C) 2003-2016 Steffen Nissen (steffen.fann@gmail.com)

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "fann.h"
#include "mushroom.h"
#include <time.h>

#define ORACLE_MODE 0

int doMushroom(int mode) {
	char* outputPath = "/opt/fann_iideaa/fann_mushroom/src/build/oracle";

	if(mode == 1) {
		outputPath = "/opt/fann_iideaa/fann_mushroom/src/build/ax";
	}
	std::ofstream outStream (outputPath);
	
	const unsigned int num_layers = 3;
	const unsigned int num_neurons_hidden = 32;
	const float desired_error = (const float) 0.0001;
	const unsigned int max_epochs = 50;
	const unsigned int epochs_between_reports = 10;
	struct fann *ann;
	struct fann_train_data *train_data, *test_data;

	unsigned int i = 0;

	printf("Creating network.\n");

	train_data = fann_read_train_from_file("/opt/fann_iideaa/datasets/mushroom.train");

	ann = fann_create_standard(num_layers,
					  train_data->num_input, num_neurons_hidden, train_data->num_output);

	printf("Training network.\n");

	fann_set_activation_function_hidden(ann, FANN_SIGMOID_SYMMETRIC);
	fann_set_activation_function_output(ann, FANN_SIGMOID);

	/*fann_set_training_algorithm(ann, FANN_TRAIN_INCREMENTAL); */

	fann_train_on_data(ann, train_data, max_epochs, epochs_between_reports, desired_error);

	printf("Testing network.\n");

	test_data = fann_read_train_from_file("/opt/fann_iideaa/datasets/mushroom.test");

	fann_reset_MSE(ann);
	for(i = 0; i < fann_length_train_data(test_data); i++)
	{
		fann_test(ann, test_data->input[i], test_data->output[i]);
	}
	
	printf("MSE error on test data: %f\n", fann_get_MSE(ann));
	
	outStream << fann_get_MSE(ann);
	outStream.close();

	printf("Saving network.\n");

	fann_save(ann, "mushroom_float.net");

	printf("Cleaning up.\n");
	fann_destroy_train(train_data);
	fann_destroy_train(test_data);
	fann_destroy(ann);

	return 0;
}

int main() {
	clock_t time_start, time_end;
	time_start = clock();
	doMushroom(ORACLE_MODE);
	time_end = clock();
	std::cout << "Time: " << (time_end - time_start)/(double)CLOCKS_PER_SEC << std::endl;
}

