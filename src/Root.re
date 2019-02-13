type repository = {
  name: string,
  description: string,
  href: string,
};

type list_of_repos = list(repository);

type state = {
  input: string,
  isLoading: bool,
  results: list_of_repos,
};

type action =
  | UpdateInput(string)
  | UpdateResults(list_of_repos)
  | Search;

/* global app state */
let initialAppState = {input: "", isLoading: false, results: []};

module Api = {
  let decodeItem = json =>
    Json.Decode.{
      name: json |> field("name", string),
      description: json |> field("description", string),
      href: json |> field("html_url", string),
    };

  let decodeItemList = json =>
    Json.Decode.(field("items", list(optional(decodeItem)), json));

  let getResults = query =>
    /* This is a local "open", it makes the Js.Promise module
       available inside of the parentheses */
    Js.Promise.(
      Fetch.fetch("https://api.github.com/search/repositories?q=" ++ query)
      |> then_(Fetch.Response.json)
      |> then_(json => decodeItemList(json) |> resolve)
      |> then_(results =>
           results
           /* Turn our items out of option types into a regular record */
           |> List.map(item =>
                switch (item) {
                | Some(item) => item
                | None => {name: "nada", description: "", href: ""}
                }
              )
           |> resolve
         )
    );
};

let reducer = (action, state) =>
  switch (action) {
  | UpdateInput(newInput) => ReasonReact.Update({...state, input: newInput})
  | UpdateResults(results) =>
    ReasonReact.Update({...state, isLoading: false, results})
  /*| Search => ReasonReact.Update({...state, isLoading: true}) */
  | Search =>
    /* update the state, then trigger a side-effect. */
    ReasonReact.UpdateWithSideEffects(
      {...state, isLoading: true},
      (
        self => {
          let value = self.state.input;
          let _ =
            Api.getResults(value)
            |> Js.Promise.then_(results => {
                 self.send(UpdateResults(results));
                 Js.Promise.resolve();
               });
          ();
        }
      ),
    )
  };