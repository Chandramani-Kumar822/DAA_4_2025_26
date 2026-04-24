async function compare() {
  const files = document.getElementById("files").files;

  if (files.length < 2) {
    alert("Upload at least 2 files");
    return;
  }

  const loader = document.getElementById("loader");
  loader.style.display = "block";

  const formData = new FormData();

  for (let f of files) {
    formData.append("files", f);
  }

  const res = await fetch("/compare", {
    method: "POST",
    body: formData,
  });

  const data = await res.json();

  loader.style.display = "none";

  if (data.error) {
    alert(data.error);
    return;
  }

  // store matches globally
  window.matchesData = data.matches || {};

  // -------- MATRIX TABLE --------
  let html = "<table><tr><th></th>";

  for (let i = 0; i < data.matrix.length; i++) {
    html += `<th>File ${i + 1}</th>`;
  }

  html += "</tr>";

  for (let i = 0; i < data.matrix.length; i++) {
    html += `<tr><th>File ${i + 1}</th>`;

    for (let j = 0; j < data.matrix[i].length; j++) {
      if (i === j) {
        html += `<td class="self-cell">100%</td>`;
      } else {
        html += `<td class="clickable" onclick="showMatches(${i}, ${j})">
                    ${data.matrix[i][j]}%
                 </td>`;
      }
    }

    html += "</tr>";
  }

  html += "</table>";

  document.getElementById("table").innerHTML = html;

  // clear previous matches
  document.getElementById("matches").innerHTML = "";
}

// -------- SHOW MATCHES FUNCTION --------
function showMatches(i, j) {
  let key = i < j ? `${i}-${j}` : `${j}-${i}`;

  let matches = window.matchesData[key];

  let html = "<div class='match-box'><h3>Matching Phrases:</h3>";

  if (!matches || matches.length === 0) {
    html += "<p>No matching phrases found</p>";
  } else {
    matches.forEach((m) => {
      html += `<p>• ${m}</p>`;
    });
  }

  html += "</div>";

  document.getElementById("matches").innerHTML = html;
}
