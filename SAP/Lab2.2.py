  # -*-coding: utf-8 -*-
from glob import glob
from datetime import datetime
from spyre import server
import pandas as pd
import matplotlib.pyplot as plt

regions = {1: 'Вінницька',
           2:  'Волинська',
           3:  'Дніпропетровська',
           4:  'Донецька',
           5:  'Житомирська',
           6:  'Закарпатська',
           7:  'Запорізька',
           8:  'Івано-Франківська',
           9:  'Київська',
           10:  'Кіровоградська',
           11:  'Луганська',
           12:  'Львівська',
           13:  'Миколаївська',
           14:  'Одеська',
           15:  'Полтавська',
           16:  'Рівенська',
           17:  'Сумська',
           18:  'Тернопільська',
           19:  'Харківська',
           20:  'Херсонська',
           21:  'Хмельницька',
           22:  'Черкаська',
           23:  'Чернівецька',
           24:  'Чернігівська',
           25:  'Республіка Крим'
           }

class StockExample(server.App):
    title = "Часовий ряд для набору даних"

    inputs = [{		"input_type":'dropdown',
                    "label": 'Набір даних',
                    "options" : [ {"label": "VCI", "value":"VCI"},
                                  {"label": "TCI", "value":"TCI"},
                                  {"label": "VHI", "value":"VHI"}],
                    "variable_name": 'dataset',
                    "action_id": "update_data" },
			{		"input_type":'dropdown',
             		"label": 'Область', 
             		"options" : [ {"label": regions[i+1], "value":i+1} for i in range(25) ],
             		"variable_name": 'region1',
           			"action_id": "update_data" },
			# {		"input_type":'dropdown',
   #           		"label": 'Область 2', 
   #           		"options" : [ {"label": regions[i+1], "value":i+1} for i in range(25) ],
   #           		"variable_name": 'region2',
   #         			"action_id": "update_data" },
      {      "input_type":'slider',
		            "label": 'Початок діапазону тижнів', 
        		    "variable_name": 'min_week', 
		            "value" : 1,
		            "min" : 1, 
		            "max" : 52,
            		"action_id" : "update_data"},
			{		"input_type":'slider',
            		"label": 'Кінець діапазону тижнів', 
            		"variable_name": 'max_week', 
            		"value" : 52,
            		"min" : 1, 
            		"max" : 52,
            		"action_id" : "update_data"},
                {
                 "input_type":'dropdown',
                 "label":'Year',
                 "options":[{'label': str(i), 'value':str(i)} for i in range(1982,2017)],
                 "key":'year',
                 "action_id":'update_data'
                }]
  
    controls = [{   "control_type" : "hidden",  
                    "label" : "Отримати часовий ряд",
                    "control_id" : "update_data"}]

    tabs = ["Графік", "Таблиця"]

    outputs = [{    "output_type" : "plot",
                    "output_id" : "plot",
                    "control_id" : "update_data",
                    "tab" : "Графік",
                    "on_page_load" : True },
				#{    "output_type" : "plot",
                #    "output_id" : "plot",
                #    "control_id" : "update_data",
                #    "tab" : "Графік",
                #    "on_page_load" : True },
                {   "output_type" : "table",
                    "output_id" : "table_id",
                    "control_id" : "update_data",
                    "tab" : "Таблиця",
                    "on_page_load" : True }]

    def getData(self, params):
        ticker = params['dataset']
        min_week = params['min_week']
        max_week = params['max_week']
        region1 = int(params['region1'])
        # region2 = int(params['region2'])
        regex1 = 'VHI/vhi_id_%s*' % regions[region1]
        # regex2 = 'VHI/vhi_id_%02i*' % region2
        df1 = pd.read_csv(glob(regex1)[0], index_col=False, header=1)
        # df2 = pd.read_csv(glob(regex2)[0], index_col=False, header=1)
        df1 = df1[['year', 'week', ticker]]
        # df2 = df2[['year', 'week', ticker]]
        df1 = df1.loc[df1['week'] >= min_week]
        df1 = df1.loc[df1['week'] <= max_week]
        # df2 = df2.loc[df2['week'] >= min_week]
        # df2 = df2.loc[df2['week'] <= max_week]
        return df1[df1['year'] == int(params['year'])]

    def getPlot(self, params):
        df1 = self.getData(params)
        # df2 = self.getData(params)[1]
        dataset = params['dataset']
        region1 = int(params['region1'])
        # region2 = int(params['region2'])
        df1 = df1.loc[df1[dataset] > 0]
        df1['date'] = pd.Series([datetime.strptime('%s-%s-1' % (year, week), '%Y-%W-%w').date() for year, week in zip(df1['year'],df1['week'])],index=df1.index)
        # df2 = df2.loc[df2[dataset] > 0]
        # df2['date'] = pd.Series([datetime.strptime('%s-%s-1' % (year, week), '%Y-%W-%w').date() for year, week in zip(df2['year'],df2['week'])],index=df2.index)
        # df = df1
        # reg1_name, reg2_name = regions[region1], regions[region2]
        # df[reg2_name] = df2[dataset]
        # df.columns = ['date', reg1_name, reg2_name]
        fig = plt.figure()
        # plt_obj = df.plot(x='date', ylim=(0,100))
        # plt_obj.set_xlabel('Year')
        # plt_obj.set_title(u"Порівняльний графік %s для областей: %s, %s" % (dataset, regions[region1], regions[region1]))
        ##plt_obj = df1.plot(x='date',y=dataset, ylim=(0,100))
        ##plt_obj.set_xlabel('Year')
        ##plt_obj.set_title(u"%s для області: %s" % (dataset, regions[region1]))
        plt_obj1 = fig.add_subplot(2,1,1)
        plt_obj1 = df1.plot(x='date',y=dataset, ylim=(0,100))
        plt_obj1.set_xlabel('Year')
        plt_obj1.set_title(u"%s для області: %s" % (dataset, regions[region1]))
        # plt_obj2 = fig.add_subplot(2,1,2)
        # plt_obj2 = df2.plot(x='date',y=dataset, ylim=(0,100))
        # plt_obj2.set_xlabel('Year')
        # plt_obj2.set_title(u"%s для області: %s" % (dataset, regions[region2]))
        fig = plt_obj1.get_figure()
        fig.autofmt_xdate(bottom=0.2, rotation=30, ha='right')
        return fig

app = StockExample()
app.launch(port=9097)
