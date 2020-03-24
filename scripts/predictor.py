# Recurrent Neural Network



# Part 1 - Data Preprocessing

# Importing the libraries
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import tensorflow as tf

# Importing the Keras libraries and packages
from keras.models import Sequential
from keras.layers import Dense
from keras.layers import LSTM
from keras.layers import Dropout



# Making the prediction
def predict(inputs):
	regressor = tf.keras.models.load_model('trained_model.h5')

	#load scaler
	from sklearn.externals import joblib
	sc = joblib.load("scaler.save")

#	print(len(inputs))
	
	inputs=inputs[0:60]
#	print("entrada original")
#	print(inputs)
#	inputs = inputs.reshape(-1,1)
	inputs = sc.transform(inputs)
#	print("entrada escalada")
#	print(inputs)

#	X_test = []
#	for i in range(60, 80):
#	X_test.append(inputs)
	X_test = np.array(inputs)
	
#	print("np array")
#	print(X_test)

	X_test = np.reshape(X_test, (X_test.shape[0], X_test.shape[1], 1))
	predicted_stock_price = regressor.predict(X_test)
	predicted_stock_price = sc.inverse_transform(predicted_stock_price)

	return predicted_stock_price


def predict2(a, b):
	return a + b


