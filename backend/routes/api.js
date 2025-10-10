const express = require('express');
const router = express.Router();
router.post('/login', (req, res) => {
    res.status(501).json({ message: 'Login endpoint not yet implemented.' });
});
router.post('/register', (req, res) => {
    res.status(501).json({ message: 'Registration endpoint not yet implemented.' });
});
router.post('/bookings/reserve', (req, res) => {   
    res.status(501).json({ message: 'Reservation endpoint not yet implemented.' });
});
router.get('/bookings/user/:userId', (req, res) => {
    res.status(501).json({ message: 'Get Bookings endpoint not yet implemented.' });
});
router.post('/iot/entry', (req, res) => {
    res.status(501).json({ message: 'IoT Entry endpoint not yet implemented.' });
});
router.post('/iot/exit', (req, res) => {
    res.status(501).json({ message: 'IoT Exit endpoint not yet implemented.' });
});

module.exports = router;
