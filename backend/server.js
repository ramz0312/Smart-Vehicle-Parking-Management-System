// backend/server.js
const express = require('express');
const app = express(); 
const apiRoutes = require('./routes/api'); 
app.use(express.json());
app.use('/api/v1', apiRoutes); 
app.get('/', (req, res) => {
    res.send('Welcome to the ParkIt Backend API!');
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`ParkIt API running on port ${PORT}`);
});
