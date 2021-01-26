import binding from '../src/binding';

describe('binding', () => {
  it('module should load', () => {
    expect(binding).not.toBeNull();
    console.log('binding:', binding);
  });
});
