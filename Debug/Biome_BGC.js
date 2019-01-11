const child_process = require('child_process');
const exec = child_process.exec;
const path = require('path');

let argv = {}
if(process.argv.length > 2) {
    for(let i=2; i< process.argv.length; i++) {
        let argc = process.argv[i]
        if(argc.startsWith('--i')) {
            argv.i = argc.replace('--i=', '')
        }
        else if(argc.startsWith('--m')) {
            argv.m = argc.replace('--m=', '')
        }
        else if(argc.startsWith('--co2')) {
            argv.co2 = argc.replace('--co2=', '')
        }
        else if(argc.startsWith('--epc')) {
            argv.epc = argc.replace('--epc=', '')
        }
        else if(argc.startsWith('--o')) {
            argv.o = argc.replace('--o=', '')
        }
    }
}
else {
    console.error('invalid input argv');
    process.exit(1);
}

let exePath = path.join(__dirname, 'Biome_BGC');
let spinupI = String.prototype.replace.call(argv.i, '.ini', '_spinup.ini');
let getIPath = iPath => `${exePath} -a --i=${iPath} --m=${argv.m} --co2=${argv.co2} \
--epc=${argv.epc} --ri=${argv.o}.endpoint --ro=${argv.o}.endpoint --o=${argv.o}`;
let spinupStr = getIPath(spinupI);
let normalStr = getIPath(argv.i);
exec(spinupStr, (err, stdout, stderr) => {
    if(err) {
        console.log(err)
        process.exit(1)
    }
    console.log(stdout)
    console.log(stderr)
    console.log('spinup succeed')
    exec(normalStr, (err, stdout, stderr) => {
        if(err) {
            console.log(err)
            process.exit(1)
        }    
        console.log(stdout)
        console.log(stderr)
        process.exit(0)
    })
})