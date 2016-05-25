import numpy as np
import pandas as pd
from random import sample
from timeit import timeit
from datetime import date, datetime, time, timedelta

arr = np.genfromtxt('household_power_consumption.txt', names=True, dtype=[date, time, '<f8', '<f8', '<f8', '<f8', '<f8', '<f8', '<f8'], delimiter=';', converters={0: lambda x: datetime.strptime(x, '%d/%m/%Y').date(), 1: lambda x: datetime.strptime(x, '%H:%M:%S').time()}, max_rows=5000)
arr = arr[~np.isnan(arr['Voltage'])]

df = pd.read_csv("household_power_consumption.txt", header=0, sep=';', na_values='?', dtype={'Global_active_power':'<f8','Global_reactive_power':'<f8','Voltage':'<f8','Global_intensity':'<f8','Sub_metering_1':'<f8','Sub_metering_2':'<f8','Sub_metering_3':'<f8'}, converters={0: lambda x: datetime.strptime(x, '%d/%m/%Y').date(), 1: lambda x: datetime.strptime(x, '%H:%M:%S').time()}, nrows=5000)
df = df.dropna()

setup_numpy  = "from __main__ import arr"
setup_pandas = "from __main__ import df"



#----------------------------------1-------------------------------------
stmt_numpy_1  = "arr[arr['Global_active_power'] > 5]"
stmt_pandas_1 = " df[ df['Global_active_power'] > 5]"

print "Processing time for task 1 with numpy:  %f" % timeit(stmt_numpy_1,  setup_numpy,  number=1)
print "Processing time for task 1 with pandas: %f" % timeit(stmt_pandas_1, setup_pandas, number=1)

#print task1_numpy.shape[0] == task1_pandas.shape[0]
#------------------------------------------------------------------------


#----------------------------------2-------------------------------------
stmt_numpy_2  = "task2_numpy  = arr[arr['Voltage'] > 235]"
stmt_pandas_2 = "task2_pandas =  df[ df['Voltage'] > 235]"

print "Processing time for task 2 with numpy:  %f" % timeit(stmt_numpy_2,  setup_numpy,  number=1)
print "Processing time for task 2 with pandas: %f" % timeit(stmt_pandas_2, setup_pandas, number=1)

# print task2_numpy.shape[0] == task2_pandas.shape[0]
#------------------------------------------------------------------------


#----------------------------------3-------------------------------------
stmt_numpy_3  = "task3_numpy  = arr[(arr['Global_intensity'] > 19) & (arr['Global_intensity'] < 20)]"
stmt_pandas_3 = "task3_pandas =  df[( df['Global_intensity'] > 19) & ( df['Global_intensity'] < 20)]"

print "Processing time for task 3 with numpy:  %f" % timeit(stmt_numpy_3, setup_numpy, number=1)
print "Processing time for task 3 with pandas: %f" % timeit(stmt_pandas_3, setup_pandas, number=1)
