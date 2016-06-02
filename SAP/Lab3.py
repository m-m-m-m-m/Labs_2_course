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

# print task3_numpy.shape[0] == task3_pandas.shape[0]
#------------------------------------------------------------------------


# # ----------------------------------4-------------------------------------
# random_list = sample(xrange(df.shape[0]),500000)
# random_arr = arr[random_list]
# random_df = df.loc[random_list]

# stmt_numpy_4 = '''
# task4_numpy_avg1 = random_arr['Sub_metering_1'].mean()
# task4_numpy_avg2 = random_arr['Sub_metering_2'].mean()
# task4_numpy_avg3 = random_arr['Sub_metering_3'].mean()'''

# stmt_pandas_4 = '''
# task4_pandas_avg1 = random_df['Sub_metering_1'].mean()
# task4_pandas_avg2 = random_df['Sub_metering_2'].mean()
# task4_pandas_avg3 = random_df['Sub_metering_3'].mean()'''

# print "Processing time for task 4 with numpy:  %f" % timeit(stmt_numpy_4, setup_numpy+", random_arr", number=1)
# print "Processing time for task 4 with pandas: %f" % timeit(stmt_pandas_4, setup_pandas+", random_df", number=1)

# # print task4_numpy_avg1 == task4_pandas_avg1
# # print task4_numpy_avg2 == task4_pandas_avg2
# # print task4_numpy_avg3 == task4_pandas_avg3
# #------------------------------------------------------------------------


# #-----------------------------------5------------------------------------
# days_list_numpy  = [arr['Date'][0] + timedelta(days=x) for x in range((arr['Date'][-1] - arr['Date'][0]).days)]
# days_list_pandas = [df['Date'].iloc[0] + timedelta(days=x) for x in range((df['Date'].iloc[-1] - df['Date'].iloc[0]).days)]

# stmt_numpy_5 = '''
# task5_numpy  = arr[arr['Time'] > time(18,00)]
# mask_numpy  = [(task5_numpy[  task5_numpy['Date'] == x]['Global_active_power'].mean() + task5_numpy[  task5_numpy['Date'] == x]['Global_reactive_power'].mean()) > 4 for x in days_list_numpy]
# days_list_numpy  = np.array(days_list_numpy)
# mask_numpy  = np.array(mask_numpy)
# days_list_numpy  = days_list_numpy[mask_numpy]
# mask_numpy  = np.array([date in days_list_numpy for date in  task5_numpy['Date']])
# task5_numpy  = task5_numpy[mask_numpy]
# task5_numpy  = task5_numpy[(task5_numpy['Sub_metering_2'] > task5_numpy['Sub_metering_1']) & (task5_numpy['Sub_metering_2'] > task5_numpy['Sub_metering_3'])]
# #indices = range(task5_numpy.size/2)[::3] + range(task5_numpy.size)[task5_numpy.size/2::4]'''

# stmt_pandas_5 = '''
# task5_numpy  = task5_numpy.take(indices)
# task5_pandas =  df[ df['Time'] > time(18,00)]
# mask_pandas = [(task5_pandas[task5_pandas['Date'] == x]['Global_active_power'].mean() + task5_pandas[task5_pandas['Date'] == x]['Global_reactive_power'].mean()) > 4 for x in days_list_pandas]
# days_list_pandas = np.array(days_list_pandas)
# mask_pandas = np.array(mask_pandas)
# days_list_pandas = days_list_pandas[mask_pandas]
# mask_pandas = np.array([date in days_list_pandas for date in task5_pandas['Date']])
# task5_pandas = task5_pandas[mask_pandas]
# task5_pandas = task5_pandas[(task5_pandas['Sub_metering_2'] > task5_pandas['Sub_metering_1']) & (task5_pandas['Sub_metering_2'] > task5_pandas['Sub_metering_3'])]
# #task5_pandas = task5_pandas.take(indices)'''

# # print "Processing time for task 5 with numpy:  %f" % timeit(stmt_numpy_5, setup_numpy+", days_list_numpy", number=1)
# # print "Processing time for task 5 with pandas: %f" % timeit(stmt_pandas_5, setup_pandas+", days_list_pandas", number=1)
