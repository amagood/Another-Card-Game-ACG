import React from 'react';

class InputRow extends React.Component {
  render() {
    return (
      <div className="input-row">
        <label htmlFor={this.props.id}>{this.props.labelText}</label>
        <input type={this.props.type} id={this.props.id} autoComplete={this.props.autoComplete} onChange={this.props.onChange} />
      </div>
    );
  }
}

export default InputRow;
