import pyPetKit
from flask import Flask, request

app = Flask(__name__)

# Pripojenie k dávkovaču
feeder = pyPetKit.Feeder('email@example.com', 'password')

@app.route('/feed', methods=['POST'])
def feed():
    grams = int(request.form['grams'])
    feeder.feed(grams)
    return 'OK'

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)

@app.route('/feed', methods=['POST'])
def feed():
    grams = int(request.form['grams'])
    feeder.feed(grams)
    return 'Krmivo dávkované'
