# Gravity and Radiation Flows in Teresina


In this repository you will find the codes and the data used to produce the results of the paper "Measuring Accessibility Using Gravity and Radiation Models" published on the Royal Society Open Science Journal. In the codes we calculate the flows of home to work trips from and to every zone in the city of Teresina in Brasil, using Gravity and Radiation models, and use the flows to measure the accessibility to employment of each zone. We calculate the accessibility before and after the introduction of Bus Rapis Transit corridors in the city. This consists in using the  matrix of travel times between zones measured by the city council before the introduction and the new predicted travel times  after the introduction. 
 
A link to the article is found here:

http://rsos.royalsocietypublishing.org/content/5/9/171668


## Code Structure 

The codes are contained in the folder codes. Here is a short explanation of what every single file contains


 calculate_old_accessibility.cpp : In this code we first calculate the flows with the gravity and radiation models, and then use the flows 
                                   to calculate the accessibility to employment of every every zone. This codes uses the old travel times 
                                   as a cost function for the flows. The values of the parameters must durind the exeution of the code (A small example will follow).

calculate_brt_accessibility.cpp :  Here we repeat the same calculation but with the predicted travel times after the brt introduction. 

calibrate_models.cpp : In this file we calibrate the models that require calibration, using Sorensen's index. 

gravity_models_functions.cpp : In this file all the functions necessary to calculates the flows using the gravity models are contained. 

radiation_models_functions.cpp : In this file all the functions necessary to calculate the flows using the radiation models are contained.

read_input_functions.cpp : All the functions to read the input data are found in this file. 


## Input Data

The input data for this project is found in the folder input_data. The files contained are :

BRT_travel_times.txt : the predicted travel times from zone to zone after the introdution of the BRT corridors.This in the new cost matrix.

OLD_travel_times.txt : the travel times of the old transport network, before the introduction of the corridors.This in the old cost matrix.

population_emplyment.txt : The population and employment population in every zone in Teresina. These are the origin and destinations. 

trips_from_survey.txt : The observed trips, measured with a survey, before the introduction of the BRT corridors. This data is 
                        used for the calibration of the models' parameters. 



## Output Data

The output data is contained in two folders: sorensen_index_data and accessbility. As the name suggests in the first folder we find the calibration data, while in the second we find the accessibilties obrained with the two different cost matrices and the different models.  


## How to Run the code  

Here how to run the code. After having cloned the repository using the command 

`git clone https://github.com/ducciopiovani/Data-on-Teresina-.git `

you should go to the codes folder `cd codes` and then compile the calibration codes with the command 

`g++ calibrate_models.cpp radiation_models_functions.cpp gravity_models_functions.cpp read_input_functions.cpp -o calibrate`

and then run it  with `./calibrate` .  

And similarly to calculate the accessbilities we first have to compile and then execute the code

`g++ calculate_accessibility.cpp radiation_models_functions.cpp gravity_models_functions.cpp read_input_functions.cpp -o compute`

when exectuing the code we have to pass the values of the parameters of the models. The order is the Beta of the gravity double constrained, the Beta of the gravity single constraiend, and the alpha of the extended radiation. Which becomes

`./compute 0.065 0.045 0.000001`






