async function sendBins() {
    const bins = JSON.parse(document.getElementById('binsInput').value);
    const response = await fetch('/add_bins', {
        method: 'POST',
        headers: {'Content-Type': 'application/json'},
        body: JSON.stringify({ bins: bins })
    });
    const data = await response.json();
    document.getElementById('output').textContent = JSON.stringify(data, null, 2);
}

async function runOptimization() {
    const response = await fetch('/run_optimization', {
        method: 'POST'
    });
    const data = await response.json();
    document.getElementById('output').textContent = JSON.stringify(data, null, 2);
}

async function getRoute() {
    const response = await fetch('/get_route');
    const data = await response.json();

    if (data && data.route) {
        displayTable(data.route);
    } else {
        document.getElementById('output').textContent = "No route data available.";
    }
}

function displayTable(route) {
    let html = `
    <table class="min-w-full bg-white border rounded">
        <thead>
            <tr class="bg-gray-200">
                <th class="py-2 px-4 border">Bin ID</th>
                <th class="py-2 px-4 border">X</th>
                <th class="py-2 px-4 border">Y</th>
                <th class="py-2 px-4 border">Fill %</th>
            </tr>
        </thead>
        <tbody>
    `;
    for (let bin of route) {
        html += `
            <tr>
                <td class="py-2 px-4 border text-center">${bin.id}</td>
                <td class="py-2 px-4 border text-center">${bin.x}</td>
                <td class="py-2 px-4 border text-center">${bin.y}</td>
                <td class="py-2 px-4 border text-center">${bin.fill}</td>
            </tr>
        `;
    }
    html += `</tbody></table>`;
    document.getElementById('output').innerHTML = html;
}
