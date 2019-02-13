/* a piece of the global state
   this component is 'interested' in*/
type ctx = {input: string};

/* this is a stateless component
     the global state is held by App (reducer component)
   */
let component = ReasonReact.statelessComponent("Form");

module Styles = {
  let card =
    ReactDOMRe.Style.make(
      ~border="2px solid #898989",
      ~borderRadius="4px",
      ~padding="1rem",
      (),
    );
};

/* appSend is pointing to its parent 'send'
   concept:
   https://medium.com/@elvesbane/revisiting-application-state-in-reasonreact-d80d440de56a
   */
let make = (~ctx: ctx, ~appSend, _children) => {
  ...component,
  render: _self =>
    <form
      onSubmit={
        ev => {
          ReactEvent.Form.preventDefault(ev);
          appSend(Root.Search);
        }
      }>
      <label htmlFor="search"> {ReasonReact.string("Search")} </label>
      <input
        id="search"
        name="search "
        value={ctx.input}
        onChange={
          ev => {
            let value = ReactEvent.Form.target(ev)##value;
            appSend(Root.UpdateInput(value));
          }
        }
      />
      <button type_="submit"> {ReasonReact.string("Submit Search")} </button>
    </form>,
};