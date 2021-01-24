const expect = require('chai').expect;
const torch = require('../lib/');
const path = require('path');

describe('tch-js', function () {
  it('ones', function () {
    const ones = torch.ones([3, 2]);

    expect([...ones.toUint8Array()]).to.deep.equal([1, 1, 1, 1, 1, 1]);
  });

  describe('tensor', function () {
    it('toFloat32Array', function () {
      const arr = new Float32Array([
        1.100000023841858,
        1.590000033378601,
        2.049999952316284,
        0.18000000715255737,
      ]);
      const tensor = torch.tensor(arr);

      expect([...tensor.toFloat32Array()]).to.deep.equal([
        1.100000023841858,
        1.590000033378601,
        2.049999952316284,
        0.18000000715255737,
      ]);
    });

    it('toUint8Array', function () {
      const arr = new Float32Array([1.1, 2.0, 3.0, 4.1]);
      const tensor = torch.tensor(arr);

      expect([...tensor.toUint8Array()]).to.deep.equal([1, 2, 3, 4]);
    });
  });

  it('load', function (done) {
    const input = torch.tensor(new Float32Array([1.5, 5.5]));

    torch.load(path.join(__dirname, 'data', 'matmul.pt'), function (err, model) {
      model.forward(input, function (err, result) {
        const output = result.toUint8Array();

        expect([...output]).to.deep.equal([3, 11]);

        done();
      });
    });
  });
});
