const testeAddon = require('./build/Release/testaddon.node');


console.log('addon', testeAddon);
console.log('addon', testeAddon.hello());
console.log('add', testeAddon.add(5, 10));
console.log('maiuscula', testeAddon.maiusculo('olamundo'));

//console.log('apagar', testeAddon.apagar());
//console.log('escrever', testeAddon.escrever('Ola mundo ruim!'));

console.log(testeAddon.tecladoConectado());


for (let i = 0; i < 100; i++) {
    testeAddon.apagar();
    testeAddon.escrever(`Contando ${i}`);
}


module.exports = testeAddon;