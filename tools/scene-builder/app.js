const state = {
  name: "Orbital Playground",
  gravityY: -9.81,
  timestep: 0.0166667,
  ambientColor: "#101820",
  entities: [
    { id: 1, name: "Ground", type: "plane", x: 0, y: -3, z: 0, size: 1, velocity: 0, mass: 0 },
    { id: 2, name: "Ball", type: "sphere", x: -4, y: 5, z: 0, size: 1, velocity: 0, mass: 1 },
    { id: 3, name: "Crate", type: "aabb", x: 4, y: 1, z: 0, size: 2, velocity: 0, mass: 2 }
  ]
};
let nextId = 4;

const entityList = document.querySelector("#entity-list");
const emptyState = document.querySelector("#empty-state");
const canvas = document.querySelector("#scene-preview");
const context = canvas.getContext("2d");

function number(value, fallback = 0) {
  const parsed = Number(value);
  return Number.isFinite(parsed) ? parsed : fallback;
}

function sceneManifest() {
  return {
    format: "3DEngineCpp.scene.v1",
    name: state.name.trim() || "Untitled Scene",
    physics: { gravity: [0, state.gravityY, 0], fixedTimestep: state.timestep },
    render: { ambientColor: state.ambientColor },
    entities: state.entities.map(({ id, ...entity }) => ({ ...entity, position: [entity.x, entity.y, entity.z] }))
      .map(({ x, y, z, ...entity }) => entity)
  };
}

function entityMarkup(entity) {
  return `<article class="entity-card" data-id="${entity.id}" data-type="${entity.type}">
    <div class="entity-card-header">
      <span class="entity-type" aria-hidden="true"></span>
      <label class="entity-card-title"><span class="sr-only">Entity name</span><input data-field="name" value="${escapeHtml(entity.name)}" maxlength="32"></label>
      <button class="remove-entity" type="button" data-action="remove" aria-label="Remove ${escapeHtml(entity.name)}" title="Remove entity">×</button>
    </div>
    <div class="entity-fields">
      <label class="field">Shape<select data-field="type"><option value="sphere" ${entity.type === "sphere" ? "selected" : ""}>Sphere</option><option value="aabb" ${entity.type === "aabb" ? "selected" : ""}>AABB</option><option value="plane" ${entity.type === "plane" ? "selected" : ""}>Plane</option></select></label>
      <label class="field">X<input data-field="x" type="number" step="0.1" value="${entity.x}"></label>
      <label class="field">Y<input data-field="y" type="number" step="0.1" value="${entity.y}"></label>
      <label class="field">Z<input data-field="z" type="number" step="0.1" value="${entity.z}"></label>
      <label class="field">Size<input data-field="size" type="number" min="0.05" step="0.1" value="${entity.size}"></label>
      <label class="field">Velocity X<input data-field="velocity" type="number" step="0.1" value="${entity.velocity}"></label>
      <label class="field">Mass<input data-field="mass" type="number" min="0" step="0.1" value="${entity.mass}"></label>
    </div>
  </article>`;
}

function escapeHtml(value) {
  return String(value).replace(/[&<>"']/g, character => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#039;" }[character]));
}

function renderEntities() {
  entityList.innerHTML = state.entities.map(entityMarkup).join("");
  emptyState.hidden = state.entities.length > 0;
  document.querySelector("#entity-count").textContent = state.entities.length;
  drawPreview();
}

function updateSceneField(event) {
  const field = event.target.id;
  if (field === "scene-name") state.name = event.target.value;
  if (field === "gravity-y") state.gravityY = number(event.target.value, -9.81);
  if (field === "timestep") state.timestep = Math.max(number(event.target.value, 0.0166667), 0.001);
  if (field === "ambient-color") state.ambientColor = event.target.value;
  drawPreview();
}

document.querySelector(".scene-panel").addEventListener("input", updateSceneField);
entityList.addEventListener("input", event => {
  const card = event.target.closest(".entity-card");
  if (!card || !event.target.dataset.field) return;
  const entity = state.entities.find(item => item.id === Number(card.dataset.id));
  const field = event.target.dataset.field;
  entity[field] = field === "name" || field === "type" ? event.target.value : number(event.target.value);
  if (field === "type") card.dataset.type = entity.type;
  drawPreview();
});
entityList.addEventListener("click", event => {
  const button = event.target.closest("[data-action='remove']");
  if (!button) return;
  const card = button.closest(".entity-card");
  state.entities = state.entities.filter(entity => entity.id !== Number(card.dataset.id));
  renderEntities();
});

document.querySelector("#add-entity").addEventListener("click", addEntity);
document.querySelector("#add-first-entity").addEventListener("click", addEntity);
document.querySelector("#reset-scene").addEventListener("click", () => {
  state.name = "Untitled Scene";
  state.gravityY = -9.81;
  state.timestep = 0.0166667;
  state.ambientColor = "#101820";
  state.entities = [];
  document.querySelector("#scene-name").value = state.name;
  document.querySelector("#gravity-y").value = state.gravityY;
  document.querySelector("#timestep").value = state.timestep;
  document.querySelector("#ambient-color").value = state.ambientColor;
  renderEntities();
});

function addEntity() {
  state.entities.push({ id: nextId++, name: `Entity ${nextId - 1}`, type: "sphere", x: 0, y: 2, z: 0, size: 1, velocity: 0, mass: 1 });
  renderEntities();
}

function drawPreview() {
  const width = canvas.width;
  const height = canvas.height;
  context.fillStyle = state.ambientColor;
  context.fillRect(0, 0, width, height);
  context.strokeStyle = "rgba(173, 209, 202, .12)";
  context.lineWidth = 1;
  for (let x = 0; x <= width; x += 40) { context.beginPath(); context.moveTo(x, 0); context.lineTo(x, height); context.stroke(); }
  for (let y = 0; y <= height; y += 40) { context.beginPath(); context.moveTo(0, y); context.lineTo(width, y); context.stroke(); }
  const mapX = value => width / 2 + value * 18;
  const mapY = value => height / 2 - value * 18;
  state.entities.forEach(entity => {
    const x = mapX(entity.x);
    const y = mapY(entity.y);
    const size = Math.max(entity.size * 18, 3);
    context.save();
    if (entity.type === "plane") {
      context.strokeStyle = "#f2c969";
      context.lineWidth = 3;
      context.setLineDash([10, 7]);
      context.beginPath(); context.moveTo(24, y); context.lineTo(width - 24, y); context.stroke();
    } else if (entity.type === "aabb") {
      context.fillStyle = "rgba(119, 184, 203, .7)";
      context.strokeStyle = "#a9dcea";
      context.lineWidth = 2;
      context.fillRect(x - size, y - size, size * 2, size * 2);
      context.strokeRect(x - size, y - size, size * 2, size * 2);
    } else {
      context.fillStyle = "rgba(200, 230, 214, .85)";
      context.strokeStyle = "#e2fff0";
      context.lineWidth = 2;
      context.beginPath(); context.arc(x, y, size, 0, Math.PI * 2); context.fill(); context.stroke();
    }
    context.fillStyle = "#eaf5f1";
    context.font = "600 12px Avenir Next, sans-serif";
    context.fillText(entity.name, Math.min(x + size + 7, width - 110), Math.max(y - size - 7, 15));
    context.restore();
  });
}

function downloadBlob(content, filename, type) {
  const link = document.createElement("a");
  link.href = URL.createObjectURL(new Blob([content], { type }));
  link.download = filename;
  link.click();
  setTimeout(() => URL.revokeObjectURL(link.href), 1000);
}

document.querySelector("#download-json").addEventListener("click", () => {
  const manifest = JSON.stringify(sceneManifest(), null, 2);
  downloadBlob(manifest, `${safeName()}.scene.json`, "application/json");
  showDownloadMessage("scene.json downloaded");
});
document.querySelector("#download-package").addEventListener("click", () => {
  const files = packageFiles();
  downloadBlob(createZip(files), `${safeName()}-package.zip`, "application/zip");
  showDownloadMessage("Runnable package downloaded");
});

function safeName() { return (state.name.trim().toLowerCase().replace(/[^a-z0-9]+/g, "-").replace(/^-|-$/g, "") || "scene"); }
function showDownloadMessage(message) { document.querySelector("#download-note").textContent = message; }

function packageFiles() {
  const manifest = JSON.stringify(sceneManifest(), null, 2);
  const preview = buildPreviewHtml(sceneManifest());
  const readme = `# ${sceneManifest().name}\n\nThis package was generated by Scene Foundry.\n\n## Run locally\nOpen index.html in a browser.\n\n## Run with Docker\n\`docker build -t ${safeName()} .\n\`docker run --rm -p 8080:80 ${safeName()}\n\nThen open http://localhost:8080.\n\nThe scene manifest is in scene.json and follows the format 3DEngineCpp.scene.v1.\n`;
  return [
    ["scene.json", manifest],
    ["index.html", preview],
    ["README.md", readme],
    ["Dockerfile", "FROM nginx:1.27-alpine\nCOPY index.html /usr/share/nginx/html/index.html\nCOPY scene.json /usr/share/nginx/html/scene.json\nEXPOSE 80\n"]
  ];
}

function buildPreviewHtml(scene) {
  const serialized = JSON.stringify(scene).replace(/</g, "\\u003c");
  return `<!doctype html><html lang="en"><head><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>${escapeHtml(scene.name)}</title><style>body{margin:0;background:#101820;color:#eaf5f1;font-family:system-ui,sans-serif}main{max-width:1000px;margin:0 auto;padding:32px}h1{font-size:clamp(2rem,5vw,4rem);margin:0 0 8px}p{color:#a9bfbe}canvas{width:100%;height:auto;border:1px solid #385057;background:#0a1116}</style></head><body><main><p>3DEngineCpp scene preview</p><h1>${escapeHtml(scene.name)}</h1><p>Gravity: ${scene.physics.gravity[1]} m/s² · ${scene.entities.length} entities</p><canvas id="preview" width="1000" height="620" aria-label="Scene preview"></canvas></main><script>const scene=${serialized};const c=document.querySelector('#preview'),x=c.getContext('2d');x.fillStyle=scene.render.ambientColor;x.fillRect(0,0,c.width,c.height);const mx=v=>c.width/2+v*22,my=v=>c.height/2-v*22;scene.entities.forEach(e=>{const p=e.position,s=Math.max(e.size*22,4),px=mx(p[0]),py=my(p[1]);x.strokeStyle=e.type==='plane'?'#f2c969':e.type==='aabb'?'#a9dcea':'#e2fff0';x.fillStyle=e.type==='plane'?'transparent':e.type==='aabb'?'rgba(119,184,203,.7)':'rgba(200,230,214,.85)';x.lineWidth=3;if(e.type==='plane'){x.setLineDash([12,8]);x.beginPath();x.moveTo(30,py);x.lineTo(c.width-30,py);x.stroke();x.setLineDash([])}else if(e.type==='aabb'){x.fillRect(px-s,py-s,s*2,s*2);x.strokeRect(px-s,py-s,s*2,s*2)}else{x.beginPath();x.arc(px,py,s,0,Math.PI*2);x.fill();x.stroke()}x.fillStyle='#eaf5f1';x.font='600 14px system-ui';x.fillText(e.name,Math.min(px+s+8,c.width-160),Math.max(py-s-8,18))});</script></body></html>`;
}

function createZip(files) {
  const encoder = new TextEncoder();
  const chunks = [];
  const central = [];
  let offset = 0;
  files.forEach(([name, content]) => {
    const nameBytes = encoder.encode(name);
    const data = encoder.encode(content);
    const crc = crc32(data);
    const header = new Uint8Array(30 + nameBytes.length);
    const view = new DataView(header.buffer);
    view.setUint32(0, 0x04034b50, true); view.setUint16(4, 20, true); view.setUint16(6, 0x800, true);
    view.setUint16(8, 0, true); view.setUint32(14, crc, true); view.setUint32(18, data.length, true); view.setUint32(22, data.length, true); view.setUint16(26, nameBytes.length, true); header.set(nameBytes, 30);
    chunks.push(header, data);
    const directory = new Uint8Array(46 + nameBytes.length); const directoryView = new DataView(directory.buffer);
    directoryView.setUint32(0, 0x02014b50, true); directoryView.setUint16(4, 20, true); directoryView.setUint16(6, 20, true); directoryView.setUint16(8, 0x800, true); directoryView.setUint32(16, crc, true); directoryView.setUint32(20, data.length, true); directoryView.setUint32(24, data.length, true); directoryView.setUint16(28, nameBytes.length, true); directoryView.setUint32(42, offset, true); directory.set(nameBytes, 46); central.push(directory); offset += header.length + data.length;
  });
  const centralOffset = offset; central.forEach(chunk => { chunks.push(chunk); offset += chunk.length; });
  const end = new Uint8Array(22); const endView = new DataView(end.buffer); endView.setUint32(0, 0x06054b50, true); endView.setUint16(8, files.length, true); endView.setUint16(10, files.length, true); endView.setUint32(12, offset - centralOffset, true); endView.setUint32(16, centralOffset, true); chunks.push(end);
  return new Blob(chunks, { type: "application/zip" });
}

function crc32(bytes) {
  let crc = 0xffffffff;
  for (const byte of bytes) { crc ^= byte; for (let bit = 0; bit < 8; bit++) crc = (crc >>> 1) ^ (crc & 1 ? 0xedb88320 : 0); }
  return (crc ^ 0xffffffff) >>> 0;
}

renderEntities();
