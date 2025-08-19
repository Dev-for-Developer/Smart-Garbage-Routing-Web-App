from flask import Flask, render_template, request, jsonify

app = Flask(__name__, static_folder='static')

bins = []
planned_route = []

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/add_bins', methods=['POST'])
def add_bins():
    global bins
    data = request.json
    bins = data['bins']
    return jsonify({'message': 'Bins received successfully', 'count': len(bins)})

@app.route('/run_optimization', methods=['POST'])
def run_optimization():
    global bins, planned_route
    planned_route = sorted(bins, key=lambda x: -x['fill'])
    return jsonify({'message': 'Optimization complete', 'route_length': len(planned_route)})

@app.route('/get_route', methods=['GET'])
def get_route():
    global planned_route
    return jsonify({'route': planned_route})

if __name__ == '__main__':
    app.run(debug=True)
