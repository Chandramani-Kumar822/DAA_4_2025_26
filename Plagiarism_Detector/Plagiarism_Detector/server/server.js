const express = require("express");
const multer = require("multer");
const { exec } = require("child_process");
const path = require("path");

const app = express();

// upload config
const upload = multer({ dest: "../uploads/" });

// serve frontend
app.use(express.static(path.join(__dirname, "../frontend")));

app.post("/compare", upload.any(), (req, res) => {
  const files = req.files;

  if (!files || files.length < 2) {
    return res.json({ error: "Upload at least 2 files" });
  }

  // build argument string
  let paths = files.map((f) => `"${f.path}"`).join(" ");

  // absolute path to exe (WINDOWS FIX)
  const exePath = path.join(__dirname, "../backend/app.exe");

  exec(`"${exePath}" ${paths}`, (err, stdout) => {
    if (err) {
      console.log(err);
      return res.json({ error: "Execution failed" });
    }

    try {
      const data = JSON.parse(stdout);
      res.json(data);
    } catch (e) {
      res.json({ error: "Parsing error", raw: stdout });
    }
  });
});

app.listen(3000, () => {
  console.log("Server running at http://localhost:3000");
});
