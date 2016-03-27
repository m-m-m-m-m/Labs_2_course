# -*-coding: utf-8 -*-
from glob import glob

from spyre import server

import pandas as pd

regions = {     1:  'Вінницька',
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

    inputs = [{     "input_type":'dropdown',
                    "label": 'Набір даних', 
                    "options" : [ {"label": "VCI", "value":"VCI"},
                                  {"label": "TCI", "value":"TCI"},
                                  {"label": "VHI", "value":"VHI"}],
                    "variable_name": 'dataset', 
                    "action_id": "update_data" },
	         {     "input_type":'dropdown',
                    "label": 'Область', 
                    "options" : [ {"label": regions[i+1], "value":i+1} for i in range(25) ],
                    "variable_name": 'region',
		    "action_id": "update_data" },
	         {	    "input_type":'slider',
		    "label": 'Початок діапазону тижнів', 
		    "variable_name": 'min_week', 
		    "value" : 1,
		    "min" : 1, 
		    "max" : 52,
		    "action_id" : "update_data"},
	      {	    "input_type":'slider',
		    "label": 'Кінець діапазону тижнів', 
		    "variable_name": 'max_week', 
		    "value" : 52,
		    "min" : 1, 
		    "max" : 52,
            "action_id" : "update_data"},]
  
    controls = [{   "control_type" : "hidden",  
                    "label" : "Отримати часовий ряд",
                    "control_id" : "update_data"}]

    tabs = ["Графік", "Таблиця"]

    outputs = [{    "output_type" : "plot",
                    "output_id" : "plot",
                    "control_id" : "update_data",
                    "tab" : "Графік",
                    "on_page_load" : True },
                {   "output_type" : "table",
                    "output_id" : "table_id",
                    "control_id" : "update_data",
                    "tab" : "Таблиця",
                    "on_page_load" : True }]

    def getData(self, params):
        ticker = params['dataset']
	min_week = params['min_week']
	max_week = params['max_week']
	region = int(params['region'])
	regex = 'VHI/vhi_id_%02i*' % region
	df = pd.read_csv(glob(regex)[0],index_col=False, header=1)
	df = df[['year', 'week', ticker]]
	df = df.loc[df['week'] >= min_week]
	df = df.loc[df['week'] <= max_week]
        return df

    def getPlot(self, params):
        df = self.getData(params)
	dataset = params['dataset']
	print dataset
	region = int(params['region'])
	df = df.loc[df[dataset] > 0]
	df['year-week'] = pd.Series(['%s-%s' % (year, week) for year, week in zip(df['year'],df['week'])], index=df.index)
        plt_obj = df.plot(x='year-week',y=dataset)
	plt_obj.set_title(u"%s для області: %s" % (dataset, regions[region]))
        fig = plt_obj.get_figure()
	fig.autofmt_xdate(bottom=0.2, rotation=30, ha='right')
        return fig

app = StockExample()
app.launch(port=9097)
