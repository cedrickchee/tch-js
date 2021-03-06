import path from 'path';
import binary from 'node-pre-gyp';

const binding_path = binary.find(
  path.resolve(path.join(__dirname, '../package.json'))
);
const binding = require(binding_path);

export default binding;
