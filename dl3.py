# 1. IMPORT LIBRARIES
import numpy as np
from tensorflow import keras
import matplotlib.pyplot as plt

# 2. LOAD DATASET
fashion_mnist = keras.datasets.fashion_mnist
(train_img, train_labels), (test_img, test_labels) = fashion_mnist.load_data()

# 3. NORMALIZE DATA
train_img = train_img / 255.0
test_img = test_img / 255.0

# CNN requires 3D input
train_img = train_img.reshape(-1, 28, 28, 1)
test_img = test_img.reshape(-1, 28, 28, 1)

# 4. CLASS NAMES
class_names = ['T-shirt/top','Trouser','Pullover','Dress','Coat','Sandal','Shirt','Sneaker','Bag','Ankle boot']

# 5. BUILD CNN MODEL
model = keras.Sequential([
    keras.Input(shape=(28, 28, 1)),
    keras.layers.Conv2D(32, (3,3), activation='relu'),
    keras.layers.MaxPooling2D((2,2)),
    keras.layers.Conv2D(64, (3,3), activation='relu'),
    keras.layers.MaxPooling2D((2,2)),
    keras.layers.Flatten(),
    keras.layers.Dense(128, activation='relu'),
    keras.layers.Dense(10, activation='softmax')
])
 
# 6. COMPILE MODEL
model.compile(
    optimizer='adam',
    loss='sparse_categorical_crossentropy',
    metrics=['accuracy']
)

# 7. TRAIN MODEL
model.fit(train_img, train_labels, epochs=5)

# 8. EVALUATE MODEL
test_loss, test_acc = model.evaluate(test_img, test_labels)
print("\nTest Accuracy:", test_acc)

# 9. MAKE PREDICTIONS
predictions = model.predict(test_img)
predicted_labels = np.argmax(predictions, axis=1)

# 10. DISPLAY RESULTS
for i in range(8):
    plt.imshow(test_img[i].reshape(28,28), cmap='gray')
    plt.title(f"Predicted: {class_names[predicted_labels[i]]}")
    plt.axis('off')
    plt.show()