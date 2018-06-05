Eos = require('eosjs') // Eos = require('./src')
// wif = '5KQwrPbwdL6PhXujxW37FSSQZ1JiwsST4cqQzDeyXtP79zkvFD3'
wif = '5J5PBZesXzvPKLBiSYeCpRhAf6ekwDFPU27EuFCJeXbbYfsbpF8'
// pubkey = 'EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV'
pubkey = 'EOS5Hzffo55Un2SByFvmPbui7M57xx6ttUCNbbJGz9DzSMgwrrF3i';
options = {broadcast: false}

config = {
    chainId: 'cf057bbfb72640471fd910bcb67639c22df9f92470936cddc1ade0e2f2e7dc4f', // 32 byte (64 char) hex string
    keyProvider: [wif], // WIF string or array of keys..
    httpEndpoint: 'http://127.0.0.1:8888',
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
 // tr.buyrambytes({
    //   payer: 'inita',
    //   receiver: 'mycontract11',
    //   bytes: 8192
    // })
    // tr.delegatebw({
    //   from: 'inita',
    //   receiver: 'mycontract11',
    //   stake_net_quantity: '100.0000 SYS',
    //   stake_cpu_quantity: '100.0000 SYS',
    //   transfer: 0
    // })

eos.transfer(
    {
        "from": "jim",
        "to": "kim",
        "quantity": "2 KAG",
        "memo": "test",
    },
    {
        authorization: "jim"
    }
)

// eos.transaction('bob', ctr => {
//     ctr.countplayers();
// })


// eos.transaction(tr => {
//     tr.newaccount({
//       creator: 'eosio',
//       name: 'maalox',
//       owner: pubkey,
//       active: pubkey
//     })
//     // tr.buyrambytes({
//     //   payer: 'inita',
//     //   receiver: 'mycontract11',
//     //   bytes: 8192
//     // })
//     // tr.delegatebw({
//     //   from: 'inita',
//     //   receiver: 'mycontract11',
//     //   stake_net_quantity: '100.0000 SYS',
//     //   stake_cpu_quantity: '100.0000 SYS',
//     //   transfer: 0
//     // })
//   })