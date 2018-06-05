Eos = require('eosjs') // Eos = require('./src')
config = {
    chainId: '579a649aae8f660aa1abbab262437596d1f388f709b0b94a9fd6bba479889ea5', // 32 byte (64 char) hex string
    keyProvider: ['5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'], // WIF string or array of keys..
    httpEndpoint: 'http://mainnet.genereos.io:80',
    // mockTransactions: () => 'pass', // or 'fail'
    // transactionHeaders: (expireInSeconds, callback) => {
    //   callback(null/*error*/, headers)
    // },
    expireInSeconds: 60,
    broadcast: true,
    debug: false, // API and transactions
    sign: true
  }
 
eos = Eos(config);

// eos
// .getBlock({block_num_or_id: 1})
// .then(result => console.log(result))


eos
.getInfo({})
.then(result => {
    console.log('-----');
    console.log(result);
})