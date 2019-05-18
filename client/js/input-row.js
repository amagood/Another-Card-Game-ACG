class InputRow extends React.Component {
  constructor(props) {
    super(props);
    this.state = {};
  }

  render() {
    return (
      <div className="input-row">
        <label htmlFor={this.props.inputId}>{this.props.labelText}</label>
        <input type={this.props.inputType} id={this.props.inputId} />
      </div>
    );
  }
}
