open Root;

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  ...component,
  initialState: () => initialAppState,
  reducer,
  render: ({state, send}) =>
    <div>
      <Form ctx={input: state.input} appSend=send />
      <Results ctx={isLoading: state.isLoading, results: state.results} />
    </div>,
};