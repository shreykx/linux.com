from flask import Flask, render_template, request
from flask_cors import CORS

from main import run_command

app = Flask(__name__)
CORS(app=app)

@app.route('/')
def index():
    return render_template('index.html')


@app.route('/api/run', methods=['POST'])
def run_command_api():
    command = request.json.get('command')
    output = run_command(command)
    return {'output': output}, 200
    
if __name__=='__main__':
    app.run('0.0.0.0', debug=True, port=8080)