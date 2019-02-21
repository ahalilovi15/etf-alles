const express = require('express');
const chalk = require('chalk');
const debug = require('debug')('app');
const morgan = require('morgan');
const path = require('path');


const mojPort = process.env.PORT || 3000;
const app = express();

const vjezba1Router = express.Router();

const vjezba2Router = express.Router();

const vjezba3Router = express.Router();

const vjezba4Router = express.Router();

app.use(morgan('tiny'));
app.use(express.static(path.join(__dirname, 'public')));
app.use('/css', express.static(path.join(__dirname, '\\node_modules\\bootstrap\\dist\\css')));
app.use('/js', express.static(path.join(__dirname, '\\node_modules\\bootstrap\\dist\\js')));
app.use('/js', express.static(path.join(__dirname, '\\node_modules\\jquery\\dist')));


vjezba1Router.route('/obavezni').get((req, res) => {
  debug(' "vjezba1/obavezni" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba1\\index.html'));
});

vjezba1Router.route('/z1').get((req, res) => {
  debug(' "vjezba1/z1" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba1\\wt-t1z1.html'));
});

vjezba1Router.route('/z2').get((req, res) => {
  debug(' "vjezba1/z2" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba1\\wt-t1z2.html'));
});

vjezba1Router.route('/z3').get((req, res) => {
  debug(' "vjezba1/z3" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba1\\wt-t1z3.html'));
});

vjezba1Router.route('/z4').get((req, res) => {
  debug(' "vjezba1/z4" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba1\\wt-t1z4.html'));
});


app.use('/vjezba1', vjezba1Router);

vjezba2Router.route('/z1').get((req, res) => {
  debug(' "vjezba2/z1" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba2\\proba.html'));
});

vjezba2Router.route('/obavezni').get((req, res) => {
  debug(' "vjezba2/obavezni" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba2\\index.html'));
});


vjezba2Router.route('/grid').get((req, res) => {
  debug(' "vjezba2/grid" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba2\\gridLayout.html'));
});

app.use('/vjezba2', vjezba2Router);

vjezba3Router.route('/z4').get((req, res) => {
  debug(' "vjezba3/z4" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba3\\zadatak4.html'));
});


vjezba3Router.route('/z3').get((req, res) => {
  debug(' "vjezba3/z3" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba3\\zadatak3.html'));
});


vjezba3Router.route('/z1').get((req, res) => {
  debug(' "vjezba3/z1" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba3\\digitron.html'));
});

app.use('/vjezba3', vjezba3Router);

vjezba4Router.route('/uvod').get((req, res) => {
  debug(' "vjezba4/uvod" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba4\\t1uvod.html'));
});

vjezba4Router.route('/z1').get((req, res) => {
  debug(' "vjezba4/z1" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba4\\z1.html'));
});

vjezba4Router.route('/z2').get((req, res) => {
  debug(' "vjezba4/z2" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba4\\z2.html'));
});

vjezba4Router.route('/z3').get((req, res) => {
  debug(' "vjezba4/z3" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba4\\z3.html'));
});

vjezba4Router.route('/z4').get((req, res) => {
  debug(' "vjezba4/z4" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba4\\z4.html'));
});

vjezba4Router.route('/z5').get((req, res) => {
  debug(' "vjezba4/z5" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba4\\z5.html'));
});

vjezba4Router.route('/z6').get((req, res) => {
  debug(' "vjezba4/z6" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba4\\z6.html'));
});

vjezba4Router.route('/app').get((req, res) => {
  debug(' "vjezba4/app" get request ');
  res.sendFile(path.join(__dirname, 'views\\vjezba4\\mashagame.html'));
});

app.use('/vjezba4', vjezba4Router);

app.get('/', (req, res) => {
  res.send('Tutorijali iz WT. Ukucati /vjezbaN/obavezni ili /vjezbaN/zX za prikaz.');
});


app.listen(mojPort, () => {
  debug(`listening on port ${chalk.green(mojPort)}`);
});
