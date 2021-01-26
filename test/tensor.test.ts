import torch from '../src';
import path from 'path';

describe('tch-js', () => {
  it('ones', () => {
    const ones = torch.ones([3, 2]);

    expect([...ones.toUint8Array()]).toEqual([1, 1, 1, 1, 1, 1]);
  });

  describe('tensor', () => {
    it('toFloat32Array', () => {
      const arr = new Float32Array([
        1.100000023841858,
        1.590000033378601,
        2.049999952316284,
        0.18000000715255737,
      ]);
      const tensor = torch.tensor(arr);

      expect([...tensor.toFloat32Array()]).toEqual([
        1.100000023841858,
        1.590000033378601,
        2.049999952316284,
        0.18000000715255737,
      ]);
    });

    it('toUint8Array', () => {
      const arr = new Float32Array([1.1, 2.0, 3.0, 4.1]);
      const tensor = torch.tensor(arr);

      expect([...tensor.toUint8Array()]).toEqual([1, 2, 3, 4]);
    });
  });

  it('load', done => {
    const input = torch.tensor(new Float32Array([1.5, 5.5]));

    torch.load(
      path.join(__dirname, 'data', 'matmul.pt'),
      (_err: any, model: any) => {
        model.forward(input, (_err: any, result: any) => {
          const output = result.toUint8Array();

          expect([...output]).toEqual([3, 11]);

          done();
        });
      }
    );
  });
});
