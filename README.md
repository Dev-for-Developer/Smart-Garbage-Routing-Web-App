# Smart Garbage Routing Web App 🚮🛣️

An intelligent **garbage collection routing system** that optimizes routes using **DFS + Greedy algorithms**.  
The system prioritizes bins based on their fill percentage, ensuring **efficient collection routes** while reducing overflow risks.  
Developed as part of my **Summer Internship Project (June–July 2025)**.

---

## 📌 Features
- 🔄 **Optimal Route Planning**: DFS + Greedy algorithm prioritizes highly filled bins first.
- 📂 **CSV Input & Output**: 
  - Input bin and map data via CSV.
  - Download planned route as `planned_route.csv`.
- 🌐 **Web Interface**: Built with Flask + TailwindCSS for easy input, execution, and visualization.
- ⚡ **Multi-language Integration**: 
  - Core algorithm in **C++**
  - Backend server with **Flask (Python)**
  - Frontend with **HTML, CSS, JavaScript**
- 🖥️ **Cross-Platform**: Runs on Windows/Linux with Python 3 and a C++ compiler.

---

## 🏗️ Architecture
1. **CSV Loader** → Reads bin data & city map edges.  
2. **Graph Builder** → Constructs adjacency list.  
3. **DFS + Greedy Algorithm** → Plans route based on fill percentage & distance.  
4. **Output** → Saves results to CSV + displays on web UI.

---

## 📂 Project Structure



Smart-Garbage-Routing-Web-App/
│── coding files/ # C++ source code (DFS + Greedy)
│── csv files/ # Input and output CSV files
│── exe files/ # Compiled executables
│── project ui/ # Frontend files (HTML, CSS, JS)
│── app.py # Flask server
│── requirements.txt # Python dependencies
│── README.md # Project documentation


---

## 🚀 Getting Started

### 🔧 Requirements
- Python 3.x  
- Flask  
- g++ compiler (for C++)  
- Browser  

### ⚙️ Installation & Run
```bash
# Clone the repository
git clone https://github.com/Dev-for-Developer/Smart-Garbage-Routing-Web-App.git
cd Smart-Garbage-Routing-Web-App

# Install dependencies
pip install -r requirements.txt

# Run Flask server
python app.py


Then open http://127.0.0.1:5000/
 in your browser.

📊 Example Workflow

Upload CSV with bin data & city map.

Run DFS + Greedy routing algorithm.

Download planned_route.csv.

View clean route table on the web UI.

📸 Screenshots

(Add screenshots of your UI here — e.g. input form, route table, CSV output.)

🧠 Learnings

Practical application of DFS + Greedy in real-world routing.

Backend-Frontend integration across C++ and Python.

Handling CSV, subprocess execution, and debugging in multi-language environments.

Full-stack development experience.

📌 Future Enhancements

IoT integration with smart garbage sensors.

Predictive analytics for route planning.

Real-time map visualization.

👨‍💻 Author

Dev Sharma
Summer Internship Project (June–July 2025)
School of Computer Science and Engineering